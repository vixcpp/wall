/**
 * @file Ids.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Simple ID generation helpers for wall.
 */

#ifndef WALL_UTIL_IDS_HPP
#define WALL_UTIL_IDS_HPP

#include <string>
#include <string_view>

namespace wall::util
{
  /**
   * @brief Small helper for generating stable string IDs.
   *
   * Format:
   *   <prefix>_<timestamp_ms>_<random_hex>
   *
   * Example:
   *   msg_1744196405123_a1b2c3d4
   */
  class Ids
  {
  public:
    /**
     * @brief Generate a generic ID with a custom prefix.
     */
    static std::string make(std::string_view prefix);

    /**
     * @brief Generate a message ID.
     */
    static std::string message();

    /**
     * @brief Generate a reaction ID.
     */
    static std::string reaction();

    /**
     * @brief Generate an event ID.
     */
    static std::string event();

    /**
     * @brief Generate a session ID.
     */
    static std::string session();

  private:
    /**
     * @brief Generate a lowercase hexadecimal random suffix.
     *
     * @param hex_len Number of hex characters to generate.
     */
    static std::string random_hex(unsigned int hex_len);
  };

} // namespace wall::util

#endif // WALL_UTIL_IDS_HPP
