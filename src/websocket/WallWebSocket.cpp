/**
 * @file WallWebSocket.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/websocket/WallWebSocket.hpp>

#include <cstdint>
#include <mutex>
#include <string>
#include <utility>

#include <vix/websocket/protocol.hpp>
#include <wall/websocket/WallEvents.hpp>
#include <vix/websocket/session.hpp>

namespace wall::websocket
{
  WallWebSocket::WallWebSocket(vix::websocket::Server &server,
                               wall::services::WallService &wall_service,
                               PresenceHub &presence_hub,
                               BroadcastService &broadcast_service,
                               std::size_t bootstrap_limit)
      : server_(server),
        wall_service_(wall_service),
        presence_hub_(presence_hub),
        broadcast_service_(broadcast_service),
        bootstrap_limit_(bootstrap_limit)
  {
  }

  void WallWebSocket::install()
  {
    server_.on_open(
        [this](Session &session)
        {
          handle_open(session);
        });

    server_.on_close(
        [this](Session &session)
        {
          handle_close(session);
        });
  }

  void WallWebSocket::broadcast_message(const wall::domain::Message &message)
  {
    server_.broadcast_json(
        std::string(WallEvents::message),
        broadcast_service_.message_created(message));

    broadcast_stats();
  }

  void WallWebSocket::broadcast_reaction(const wall::domain::Reaction &reaction)
  {
    server_.broadcast_json(
        std::string(WallEvents::reaction),
        broadcast_service_.reaction_created(reaction));

    broadcast_stats();
  }

  void WallWebSocket::broadcast_presence()
  {
    server_.broadcast_json(
        std::string(WallEvents::presence),
        broadcast_service_.presence_updated(
            static_cast<std::int64_t>(presence_hub_.online_count())));
  }

  void WallWebSocket::broadcast_stats()
  {
    const auto stats =
        wall_service_.stats(presence_hub_.online_count());

    server_.broadcast_json(
        std::string(WallEvents::stats),
        broadcast_service_.stats_updated(stats));
  }

  void WallWebSocket::handle_open(Session &session)
  {
    const std::string session_id = attach_session(session);
    (void)session_id;
  }

  void WallWebSocket::handle_close(Session &session)
  {
    const std::string session_id = detach_session(session);
    (void)session_id;
  }

  void WallWebSocket::send_hello(Session &session, const std::string &session_id)
  {
    const auto latest_messages =
        wall_service_.latest_messages(bootstrap_limit_);

    const auto stats =
        wall_service_.stats(presence_hub_.online_count());

    send_event(
        session,
        WallEvents::hello,
        broadcast_service_.hello(
            session_id,
            static_cast<std::int64_t>(presence_hub_.online_count()),
            stats,
            latest_messages));
  }

  void WallWebSocket::send_event(Session &session,
                                 std::string_view type,
                                 vix::json::kvs payload)
  {
    vix::websocket::JsonMessage message;
    message.kind = "event";
    message.type = std::string(type);
    message.room = "";
    message.payload = std::move(payload);

    session.send_text(vix::websocket::JsonMessage::serialize(message));
  }

  std::string WallWebSocket::attach_session(Session &session)
  {
    auto presence = presence_hub_.connect();
    const std::string session_id = presence.session_id();

    std::lock_guard<std::mutex> lock(mutex_);
    session_ids_[session_key(session)] = session_id;
    return session_id;
  }

  std::string WallWebSocket::detach_session(Session &session)
  {
    std::string session_id;

    {
      std::lock_guard<std::mutex> lock(mutex_);
      const auto key = session_key(session);
      const auto it = session_ids_.find(key);

      if (it != session_ids_.end())
      {
        session_id = it->second;
        session_ids_.erase(it);
      }
    }

    if (!session_id.empty())
    {
      presence_hub_.disconnect(session_id);
    }

    return session_id;
  }

  std::uintptr_t WallWebSocket::session_key(Session &session) noexcept
  {
    return reinterpret_cast<std::uintptr_t>(&session);
  }

  vix::websocket::Server &WallWebSocket::server() noexcept
  {
    return server_;
  }

  const vix::websocket::Server &WallWebSocket::server() const noexcept
  {
    return server_;
  }

} // namespace wall::websocket
