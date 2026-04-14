(() => {
  "use strict";

  const state = {
    sessionId: "",
    socket: null,
    reconnectTimer: null,
    messages: [],
    stats: {
      total_messages: 0,
      total_reactions: 0,
      online_sessions: 0,
      generated_at_ms: 0,
    },
  };

  const WS_PORT = 9090;
  const WS_PATH = "/";

  let dom = null;
  let statsPollTimer = null;

  function startStatsPolling() {
    stopStatsPolling();

    statsPollTimer = setInterval(() => {
      loadStats().catch((error) => {
        console.error("Failed to refresh stats:", error);
      });
    }, 2000);
  }

  function stopStatsPolling() {
    if (statsPollTimer !== null) {
      clearInterval(statsPollTimer);
      statsPollTimer = null;
    }
  }

  function getDom() {
    return {
      form: document.getElementById("message-form"),
      username: document.getElementById("username"),
      message: document.getElementById("message"),
      messageCount: document.getElementById("message-count"),
      submitButton: document.getElementById("submit-button"),
      formErrors: document.getElementById("form-errors"),

      statMessages: document.getElementById("stat-messages"),
      statReactions: document.getElementById("stat-reactions"),
      statOnline: document.getElementById("stat-online"),

      connectionDot: document.getElementById("connection-dot"),
      connectionText: document.getElementById("connection-text"),
      sessionId: document.getElementById("session-id"),

      feed: document.getElementById("feed"),
      feedEmpty: document.getElementById("feed-empty"),
    };
  }

  function escapeHtml(value) {
    return String(value)
      .replaceAll("&", "&amp;")
      .replaceAll("<", "&lt;")
      .replaceAll(">", "&gt;")
      .replaceAll('"', "&quot;")
      .replaceAll("'", "&#039;");
  }

  function formatTime(ms) {
    if (!ms || Number.isNaN(ms)) {
      return "-";
    }

    return new Date(ms).toLocaleString();
  }

  function setConnectionStatus(kind, text) {
    if (!dom?.connectionText || !dom?.connectionDot) {
      return;
    }

    dom.connectionText.textContent = text;
    dom.connectionDot.className = "status-dot";

    if (kind === "online") {
      dom.connectionDot.classList.add("status-dot--online");
      return;
    }

    if (kind === "offline") {
      dom.connectionDot.classList.add("status-dot--offline");
      return;
    }

    dom.connectionDot.classList.add("status-dot--connecting");
  }

  function setSessionId(value) {
    state.sessionId = value || "";
    if (dom?.sessionId) {
      dom.sessionId.textContent = state.sessionId || "-";
    }
  }

  function showErrors(errors) {
    if (!dom?.formErrors) {
      return;
    }

    if (!errors || errors.length === 0) {
      dom.formErrors.hidden = true;
      dom.formErrors.innerHTML = "";
      return;
    }

    dom.formErrors.hidden = false;
    dom.formErrors.innerHTML = `
      <ul>
        ${errors.map((error) => `<li>${escapeHtml(error)}</li>`).join("")}
      </ul>
    `;
  }

  function updateMessageCount() {
    if (!dom?.message || !dom?.messageCount) {
      return;
    }

    const value = dom.message.value || "";
    dom.messageCount.textContent = `${value.length} / 280`;
  }

  function renderStats() {
    if (!dom) {
      return;
    }

    if (dom.statMessages) {
      dom.statMessages.textContent = String(state.stats.total_messages ?? 0);
    }

    if (dom.statReactions) {
      dom.statReactions.textContent = String(state.stats.total_reactions ?? 0);
    }

    if (dom.statOnline) {
      dom.statOnline.textContent = String(state.stats.online_sessions ?? 0);
    }
  }

  function makeReactionButton(messageId) {
    const button = document.createElement("button");
    button.type = "button";
    button.className = "reaction-button";
    button.textContent = "⚡";
    button.setAttribute("aria-label", "Send lightning reaction");

    button.addEventListener("click", async () => {
      try {
        await postReaction(messageId, "⚡");
        await loadStats();
      } catch (error) {
        console.error("Failed to send reaction:", error);
      }
    });

    return button;
  }

  function renderMessageItem(message) {
    const article = document.createElement("article");
    article.className = "message-card";
    article.dataset.messageId = message.id;

    const header = document.createElement("div");
    header.className = "message-card__head";

    const user = document.createElement("strong");
    user.className = "message-card__user";
    user.textContent = message.username || "anonymous";

    const time = document.createElement("span");
    time.className = "message-card__time";
    time.textContent = formatTime(message.created_at_ms);

    const body = document.createElement("p");
    body.className = "message-card__text";
    body.textContent = message.text || "";

    const actions = document.createElement("div");
    actions.className = "message-card__actions";
    actions.appendChild(makeReactionButton(message.id));

    header.appendChild(user);
    header.appendChild(time);

    article.appendChild(header);
    article.appendChild(body);
    article.appendChild(actions);

    return article;
  }

  function renderFeed() {
    if (!dom?.feed || !dom?.feedEmpty) {
      return;
    }

    dom.feed.innerHTML = "";

    if (!state.messages || state.messages.length === 0) {
      dom.feedEmpty.hidden = false;
      return;
    }

    dom.feedEmpty.hidden = true;

    for (const message of state.messages) {
      dom.feed.appendChild(renderMessageItem(message));
    }
  }

  function upsertMessage(message) {
    if (!message || !message.id) {
      return;
    }

    const index = state.messages.findIndex((item) => item.id === message.id);

    if (index >= 0) {
      state.messages[index] = message;
    } else {
      state.messages.unshift(message);
    }

    state.messages.sort((a, b) => {
      const left = Number(a.created_at_ms || 0);
      const right = Number(b.created_at_ms || 0);
      return right - left;
    });

    renderFeed();
  }

  function setMessages(messages) {
    state.messages = Array.isArray(messages) ? [...messages] : [];
    state.messages.sort((a, b) => {
      const left = Number(a.created_at_ms || 0);
      const right = Number(b.created_at_ms || 0);
      return right - left;
    });
    renderFeed();
  }

  function setStats(stats) {
    state.stats = {
      total_messages: Number(stats?.total_messages ?? 0),
      total_reactions: Number(stats?.total_reactions ?? 0),
      online_sessions: Number(stats?.online_sessions ?? 0),
      generated_at_ms: Number(stats?.generated_at_ms ?? 0),
    };

    renderStats();
  }

  async function fetchJson(url, options = {}) {
    const response = await fetch(url, {
      headers: {
        "Content-Type": "application/json",
      },
      ...options,
    });

    let payload = null;

    try {
      payload = await response.json();
    } catch (_) {
      payload = null;
    }

    if (!response.ok) {
      const message =
        payload?.errors?.join(", ") ||
        payload?.message ||
        `HTTP ${response.status}`;
      throw new Error(message);
    }

    return payload;
  }

  async function loadMessages() {
    const payload = await fetchJson("/api/messages?limit=20");
    setMessages(payload.messages || []);
  }

  async function loadStats() {
    const payload = await fetchJson("/api/stats");
    setStats(payload.stats || {});
  }

  async function postMessage(username, text) {
    return fetchJson("/api/messages", {
      method: "POST",
      body: JSON.stringify({
        username,
        text,
      }),
    });
  }

  async function postReaction(messageId, kind) {
    return fetchJson("/api/reactions", {
      method: "POST",
      body: JSON.stringify({
        message_id: messageId,
        kind,
      }),
    });
  }

  async function handleSubmit(event) {
    event.preventDefault();

    showErrors([]);

    if (dom?.submitButton) {
      dom.submitButton.disabled = true;
    }

    try {
      const username = dom?.username?.value || "";
      const text = dom?.message?.value || "";

      const payload = await postMessage(username, text);

      if (payload?.message) {
        upsertMessage(payload.message);
      }

      await loadStats();

      if (dom?.message) {
        dom.message.value = "";
      }

      updateMessageCount();
    } catch (error) {
      showErrors([error.message || "Failed to post message"]);
    } finally {
      if (dom?.submitButton) {
        dom.submitButton.disabled = false;
      }
    }
  }

  function websocketUrl() {
    const protocol = window.location.protocol === "https:" ? "wss:" : "ws:";
    const host = window.location.hostname || "localhost";
    return `${protocol}//${host}:${WS_PORT}${WS_PATH}`;
  }

  function clearReconnectTimer() {
    if (state.reconnectTimer !== null) {
      clearTimeout(state.reconnectTimer);
      state.reconnectTimer = null;
    }
  }

  function scheduleReconnect() {
    clearReconnectTimer();
    state.reconnectTimer = setTimeout(() => {
      connectWebSocket();
    }, 2000);
  }

  function closeCurrentSocket() {
    if (!state.socket) {
      return;
    }

    const socket = state.socket;
    state.socket = null;

    try {
      socket.close();
    } catch (_) {
      // ignore close errors
    }
  }

  function connectWebSocket() {
    clearReconnectTimer();
    closeCurrentSocket();

    const url = websocketUrl();
    console.log("[wall] connecting ws:", url);
    setConnectionStatus("connecting", "Connecting...");

    const socket = new WebSocket(url);
    state.socket = socket;

    socket.addEventListener("open", () => {
      if (state.socket !== socket) {
        return;
      }

      console.log("[wall] ws connected");
      setConnectionStatus("online", "Connected");
    });

    socket.addEventListener("close", (event) => {
      if (state.socket === socket) {
        state.socket = null;
      }

      console.log("[wall] ws closed", event.code, event.reason);
      setConnectionStatus("offline", "Disconnected");
      scheduleReconnect();
    });

    socket.addEventListener("error", (event) => {
      console.log("[wall] ws error", event);
      if (state.socket !== socket) {
        return;
      }

      setConnectionStatus("offline", "Connection error");
    });

    socket.addEventListener("message", (event) => {
      if (state.socket !== socket) {
        return;
      }

      console.log("[wall] ws message:", event.data);
      handleSocketMessage(event.data);
    });
  }

  function normalizeSocketMessage(data) {
    if (!data || typeof data !== "object") {
      return null;
    }

    const type = typeof data.type === "string" ? data.type : "";
    const payload =
      data.payload && typeof data.payload === "object" ? data.payload : {};

    if (!type) {
      return null;
    }

    return { type, payload };
  }

  function handleSocketMessage(raw) {
    let data = null;

    try {
      data = JSON.parse(raw);
    } catch (error) {
      console.warn("Invalid socket payload:", raw);
      return;
    }

    const msg = normalizeSocketMessage(data);
    if (!msg) {
      console.warn("Unsupported socket message shape:", data);
      return;
    }

    const { type, payload } = msg;

    if (type === "wall.hello") {
      if (payload.session_id) {
        setSessionId(payload.session_id);
      }

      if (Array.isArray(payload.latest_messages)) {
        setMessages(payload.latest_messages);
      }

      if (payload.stats) {
        setStats(payload.stats);
      } else {
        setStats(payload);
      }

      return;
    }

    if (type === "wall.message") {
      upsertMessage(payload);
      return;
    }

    if (type === "wall.reaction") {
      loadStats().catch((error) => {
        console.error("Failed to refresh stats after reaction:", error);
      });
      return;
    }

    if (type === "wall.presence") {
      state.stats.online_sessions = Number(payload.online_sessions ?? 0);
      renderStats();
      return;
    }

    if (type === "wall.stats") {
      setStats(payload);
      return;
    }

    if (type === "wall.error") {
      const errors = Array.isArray(payload.errors)
        ? payload.errors
        : ["Unknown realtime error"];
      showErrors(errors);
    }
  }

  async function bootstrap() {
    dom = getDom();

    if (!dom.form || !dom.message || !dom.feed) {
      console.error("[wall] missing required DOM nodes, bootstrap aborted");
      return;
    }

    updateMessageCount();
    renderStats();
    renderFeed();
    setConnectionStatus("connecting", "Connecting...");

    dom.form.addEventListener("submit", handleSubmit);
    dom.message.addEventListener("input", updateMessageCount);

    try {
      await Promise.all([loadMessages(), loadStats()]);
    } catch (error) {
      console.error("Bootstrap failed:", error);
    }

    startStatsPolling();
    connectWebSocket();
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", bootstrap, { once: true });
  } else {
    bootstrap();
  }
})();
