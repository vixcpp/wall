/**
 * @file WallEvents.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#ifndef WALL_WEBSOCKET_WALLEVENTS_HPP
#define WALL_WEBSOCKET_WALLEVENTS_HPP

#include <string_view>

namespace wall::websocket
{
  /**
   * @brief Centralized event names used by wall realtime flows.
   */
  class WallEvents
  {
  public:
    /**
     * @brief Event emitted when a new message is created.
     */
    static constexpr std::string_view message = "wall.message";

    /**
     * @brief Event emitted when a new reaction is created.
     */
    static constexpr std::string_view reaction = "wall.reaction";

    /**
     * @brief Event emitted when presence changes.
     */
    static constexpr std::string_view presence = "wall.presence";

    /**
     * @brief Event emitted when stats are updated.
     */
    static constexpr std::string_view stats = "wall.stats";

    /**
     * @brief Event emitted when a validation error occurs.
     */
    static constexpr std::string_view error = "wall.error";

    /**
     * @brief Event emitted when the client first connects and receives bootstrap data.
     */
    static constexpr std::string_view hello = "wall.hello";

    /**
     * @brief Check whether an event name belongs to wall namespace.
     */
    static constexpr bool is_wall_event(std::string_view name) noexcept
    {
      return name == message ||
             name == reaction ||
             name == presence ||
             name == stats ||
             name == error ||
             name == hello;
    }
  };

} // namespace wall::websocket

#endif // WALL_WEBSOCKET_WALLEVENTS_HPP
