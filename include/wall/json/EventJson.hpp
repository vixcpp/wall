/**
 * @file EventJson.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_JSON_EVENTJSON_HPP
#define WALL_JSON_EVENTJSON_HPP

#include <cstdint>
#include <string_view>

#include <vix/json/Simple.hpp>

#include <wall/domain/Message.hpp>
#include <wall/domain/Reaction.hpp>
#include <wall/domain/Stats.hpp>

namespace wall::json
{
  /**
   * @brief JSON helpers for realtime wall events.
   *
   * Event shape:
   * {
   *   "type": "<event_name>",
   *   "payload": { ... }
   * }
   */
  class EventJson
  {
  public:
    /**
     * @brief Build a generic event object.
     *
     * The payload is accepted by value so nested JSON objects are moved
     * into the final event object instead of being referenced through
     * short-lived temporaries.
     */
    static vix::json::kvs make(std::string_view type,
                               vix::json::token payload);

    /**
     * @brief Build a wall.message event.
     */
    static vix::json::kvs message_created(const wall::domain::Message &message);

    /**
     * @brief Build a wall.reaction event.
     */
    static vix::json::kvs reaction_created(const wall::domain::Reaction &reaction);

    /**
     * @brief Build a wall.presence event.
     */
    static vix::json::kvs presence_updated(std::int64_t online_sessions);

    /**
     * @brief Build a wall.stats event.
     */
    static vix::json::kvs stats_updated(const wall::domain::Stats &stats);
  };

} // namespace wall::json

#endif // WALL_JSON_EVENTJSON_HPP
