/**
 * @file BroadcastService.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Realtime broadcast payload builder for wall.
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
   * @brief Small helper service that builds broadcastable wall events.
   *
   * This service does not send data by itself.
   * It only centralizes event creation so the WebSocket layer stays clean.
   */
  class BroadcastService
  {
  public:
    /**
     * @brief Build a broadcast payload for a created message.
     */
    [[nodiscard]] vix::json::kvs message_created(
        const wall::domain::Message &message) const;

    /**
     * @brief Build a broadcast payload for a created reaction.
     */
    [[nodiscard]] vix::json::kvs reaction_created(
        const wall::domain::Reaction &reaction) const;

    /**
     * @brief Build a broadcast payload for updated presence.
     */
    [[nodiscard]] vix::json::kvs presence_updated(
        std::int64_t online_sessions) const;

    /**
     * @brief Build a broadcast payload for updated stats.
     */
    [[nodiscard]] vix::json::kvs stats_updated(
        const wall::domain::Stats &stats) const;

    /**
     * @brief Build a bootstrap payload sent when a client connects.
     */
    [[nodiscard]] vix::json::kvs hello(
        const std::string &session_id,
        std::int64_t online_sessions,
        const wall::domain::Stats &stats,
        const std::vector<wall::domain::Message> &latest_messages) const;

    /**
     * @brief Build a broadcast payload for an error event.
     */
    [[nodiscard]] vix::json::kvs error(
        const std::vector<std::string> &errors) const;
  };

} // namespace wall::websocket

#endif // WALL_WEBSOCKET_BROADCASTSERVICE_HPP
