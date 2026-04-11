/**
 * @file Strings.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_UTIL_STRINGS_HPP
#define WALL_UTIL_STRINGS_HPP

#include <string>
#include <string_view>

namespace wall::util
{
  /**
   * @brief String utilities for wall.
   *
   * This wraps vix::utils and adds app-specific helpers.
   */
  class Strings
  {
  public:
    /**
     * @brief Trim + normalize whitespace.
     */
    static std::string clean(std::string_view input);

    /**
     * @brief Normalize a username.
     *
     * - trim
     * - lowercase
     * - remove invalid chars
     */
    static std::string normalize_username(std::string_view input);

    /**
     * @brief Limit string length safely.
     */
    static std::string limit(std::string_view input, std::size_t max_len);

    /**
     * @brief Check if string is empty or only spaces.
     */
    static bool is_blank(std::string_view input) noexcept;

    /**
     * @brief Basic safe text filter (for demo).
     *
     * Removes control characters.
     */
    static std::string sanitize_text(std::string_view input);
  };

} // namespace wall::util

#endif // WALL_UTIL_STRINGS_HPP
