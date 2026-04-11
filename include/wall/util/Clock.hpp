/**
 * @file Clock.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#ifndef WALL_UTIL_CLOCK_HPP
#define WALL_UTIL_CLOCK_HPP

#include <cstdint>

#include <vix/time/Timestamp.hpp>
#include <vix/time/Duration.hpp>

namespace wall::util
{
  /**
   * @brief Clock utilities for wall.
   *
   * This is a thin wrapper around vix::time.
   * We keep it minimal and focused on what wall needs.
   */
  class Clock
  {
  public:
    /**
     * @brief Current timestamp (nanoseconds since epoch).
     */
    static vix::time::Timestamp now() noexcept;

    /**
     * @brief Current time in milliseconds since epoch.
     *
     * Useful for:
     * - JSON responses
     * - frontend timestamps
     * - logs
     */
    static std::int64_t now_ms() noexcept;

    /**
     * @brief Current time in seconds since epoch.
     */
    static std::int64_t now_sec() noexcept;

    /**
     * @brief Compute elapsed duration since a timestamp.
     */
    static vix::time::Duration since(const vix::time::Timestamp &t0) noexcept;

    /**
     * @brief Compute elapsed milliseconds since a timestamp.
     */
    static std::int64_t since_ms(const vix::time::Timestamp &t0) noexcept;
  };

} // namespace wall::util

#endif // WALL_UTIL_CLOCK_HPP
