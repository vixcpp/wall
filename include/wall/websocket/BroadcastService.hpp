/**
 * @file BroadcastService.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_WEBSOCKET_BROADCASTSERVICE_HPP
#define WALL_WEBSOCKET_BROADCASTSERVICE_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <vix/json/Simple.hpp>

#include <wall/domain/Message.hpp>
#include <wall/domain/Reaction.hpp>
#include <wall/domain/Stats.hpp>

namespace wall::websocket
{
  /**
   * @brief Small helper service that builds broadcastable wall payloads.
   *
   * This service does not send data by itself.
   * It only centralizes payload creation so the WebSocket layer stays clean.
   *
   * Important:
   * - this service returns payload objects only
   * - the outer event envelope is built by the WebSocket layer
   */
  class BroadcastService
  {
  public:
    /**
     * @brief Build the payload for a created message event.
     */
    [[nodiscard]] vix::json::kvs message_created(
        const wall::domain::Message &message) const;

    /**
     * @brief Build the payload for a created reaction event.
     */
    [[nodiscard]] vix::json::kvs reaction_created(
        const wall::domain::Reaction &reaction) const;

    /**
     * @brief Build the payload for an updated presence event.
     */
    [[nodiscard]] vix::json::kvs presence_updated(
        std::int64_t online_sessions) const;

    /**
     * @brief Build the payload for an updated stats event.
     */
    [[nodiscard]] vix::json::kvs stats_updated(
        const wall::domain::Stats &stats) const;

    /**
     * @brief Build the bootstrap payload sent when a client connects.
     */
    [[nodiscard]] vix::json::kvs hello(
        const std::string &session_id,
        std::int64_t online_sessions,
        const wall::domain::Stats &stats,
        const std::vector<wall::domain::Message> &latest_messages) const;

    /**
     * @brief Build the payload for an error event.
     */
    [[nodiscard]] vix::json::kvs error(
        const std::vector<std::string> &errors) const;
  };

} // namespace wall::websocket

#endif // WALL_WEBSOCKET_BROADCASTSERVICE_HPP
