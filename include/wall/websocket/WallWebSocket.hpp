/**
 * @file WallWebSocket.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#ifndef WALL_WEBSOCKET_WALLWEBSOCKET_HPP
#define WALL_WEBSOCKET_WALLWEBSOCKET_HPP

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

#include <vix/websocket.hpp>

#include <wall/domain/Message.hpp>
#include <wall/domain/Reaction.hpp>
#include <wall/services/WallService.hpp>
#include <wall/websocket/BroadcastService.hpp>
#include <wall/websocket/PresenceHub.hpp>

namespace wall::websocket
{
  /**
   * @brief Realtime adapter for the wall application.
   *
   * Responsibilities:
   * - track connected sessions
   * - send a bootstrap payload on connect
   * - broadcast message/reaction/presence/stats updates
   */
  class WallWebSocket
  {
  public:
    /**
     * @brief Construct a wall WebSocket adapter.
     *
     * @param server Active Vix WebSocket server.
     * @param wall_service Central wall application service.
     * @param presence_hub In-memory presence tracker.
     * @param broadcast_service Realtime payload builder.
     * @param bootstrap_limit Number of latest messages sent on connect.
     */
    WallWebSocket(vix::websocket::Server &server,
                  wall::services::WallService &wall_service,
                  PresenceHub &presence_hub,
                  BroadcastService &broadcast_service,
                  std::size_t bootstrap_limit = 20);

    /**
     * @brief Register WebSocket callbacks on the underlying server.
     */
    void install();

    /**
     * @brief Broadcast a newly created message.
     */
    void broadcast_message(const wall::domain::Message &message);

    /**
     * @brief Broadcast a newly created reaction.
     */
    void broadcast_reaction(const wall::domain::Reaction &reaction);

    /**
     * @brief Broadcast current presence.
     */
    void broadcast_presence();

    /**
     * @brief Broadcast current stats.
     */
    void broadcast_stats();

  private:
    using Session = vix::websocket::Session;

    vix::websocket::Server &server_;
    wall::services::WallService &wall_service_;
    PresenceHub &presence_hub_;
    BroadcastService &broadcast_service_;
    std::size_t bootstrap_limit_{20};

    mutable std::mutex mutex_;
    std::unordered_map<std::uintptr_t, std::string> session_ids_{};

    void handle_open(Session &session);
    void handle_close(Session &session);

    void send_hello(Session &session, const std::string &session_id);
    void send_event(Session &session,
                    std::string_view type,
                    const vix::json::kvs &payload);

    std::string attach_session(Session &session);
    std::string detach_session(Session &session);
    std::string find_session_id(Session &session) const;

    static std::uintptr_t session_key(Session &session) noexcept;
  };

} // namespace wall::websocket

#endif // WALL_WEBSOCKET_WALLWEBSOCKET_HPP
