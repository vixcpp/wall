/**
 * @file Env.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Environment helpers for wall.
 *
 * This is a thin app-specific wrapper around vix::utils::Env.
 */

#ifndef WALL_UTIL_ENV_HPP
#define WALL_UTIL_ENV_HPP

#include <string>

namespace wall::util
{
  /**
   * @brief Environment accessors for wall.
   *
   * These helpers centralize the environment variable names used by the app.
   */
  class Env
  {
  public:
    /**
     * @brief Get the current application environment.
     *
     * Example values:
     * - development
     * - production
     * - test
     */
    static std::string app_env();

    /**
     * @brief Get the application root directory.
     *
     * Relative paths such as the SQLite database path are resolved
     * from this directory.
     */
    static std::string app_root();

    /**
     * @brief True if APP_ENV is "production".
     */
    static bool is_production();

    /**
     * @brief True if APP_ENV is "development".
     */
    static bool is_development();

    /**
     * @brief HTTP listen host.
     */
    static std::string host();

    /**
     * @brief HTTP listen port.
     */
    static int port();

    /**
     * @brief Public base URL.
     */
    static std::string public_url();

    /**
     * @brief Path to the SQLite database file.
     */
    static std::string database_path();

    /**
     * @brief Directory where logs are written.
     */
    static std::string log_dir();

    /**
     * @brief Maximum allowed message length.
     */
    static int max_message_length();

    /**
     * @brief Maximum allowed username length.
     */
    static int max_username_length();

    /**
     * @brief Rate limit window in seconds.
     */
    static int rate_limit_window_sec();

    /**
     * @brief Maximum number of requests allowed during the rate limit window.
     */
    static int rate_limit_max_requests();

    /**
     * @brief Debug mode flag.
     */
    static bool debug();
  };

} // namespace wall::util

#endif // WALL_UTIL_ENV_HPP
