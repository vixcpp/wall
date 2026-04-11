/**
 * @file WallConfig.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Application configuration for wall.
 */

#ifndef WALL_CONFIG_WALLCONFIG_HPP
#define WALL_CONFIG_WALLCONFIG_HPP

#include <string>

namespace wall::config
{
  /**
   * @brief Runtime configuration for the wall application.
   *
   * This object centralizes all resolved configuration values used by the app.
   *
   * It is responsible for:
   * - reading values from environment variables
   * - normalizing paths
   * - exposing a consistent runtime configuration
   *
   * Paths such as the SQLite database and log directory are resolved
   * relative to the application root.
   */
  class WallConfig
  {
  public:
    /**
     * @brief Build a config instance from environment variables.
     */
    [[nodiscard]] static WallConfig from_env();

    /**
     * @brief Default constructor.
     */
    WallConfig() = default;

    /**
     * @brief Full constructor.
     *
     * @param app_env Application environment (development, production, ...)
     * @param app_root Root directory of the application
     * @param host HTTP host
     * @param port HTTP port
     * @param public_url Public base URL
     * @param database_path SQLite database path (relative or absolute)
     * @param log_dir Log directory path (relative or absolute)
     * @param max_message_length Maximum allowed message length
     * @param max_username_length Maximum allowed username length
     * @param rate_limit_window_sec Rate limit window in seconds
     * @param rate_limit_max_requests Max requests in the rate limit window
     * @param debug Enable debug mode
     */
    WallConfig(std::string app_env,
               std::string app_root,
               std::string host,
               int port,
               std::string public_url,
               std::string database_path,
               std::string log_dir,
               int max_message_length,
               int max_username_length,
               int rate_limit_window_sec,
               int rate_limit_max_requests,
               bool debug);

    /**
     * @brief Get the application environment.
     */
    [[nodiscard]] const std::string &app_env() const noexcept;

    /**
     * @brief Get the application root directory.
     *
     * All relative paths are resolved from this directory.
     */
    [[nodiscard]] const std::string &app_root() const noexcept;

    /**
     * @brief Get the HTTP host.
     */
    [[nodiscard]] const std::string &host() const noexcept;

    /**
     * @brief Get the HTTP port.
     */
    [[nodiscard]] int port() const noexcept;

    /**
     * @brief Get the public base URL.
     */
    [[nodiscard]] const std::string &public_url() const noexcept;

    /**
     * @brief Get the SQLite database path.
     *
     * This path is always normalized to an absolute path.
     */
    [[nodiscard]] const std::string &database_path() const noexcept;

    /**
     * @brief Get the log directory.
     *
     * This path is always normalized to an absolute path.
     */
    [[nodiscard]] const std::string &log_dir() const noexcept;

    /**
     * @brief Get the maximum allowed message length.
     */
    [[nodiscard]] int max_message_length() const noexcept;

    /**
     * @brief Get the maximum allowed username length.
     */
    [[nodiscard]] int max_username_length() const noexcept;

    /**
     * @brief Get the rate-limit window in seconds.
     */
    [[nodiscard]] int rate_limit_window_sec() const noexcept;

    /**
     * @brief Get the max requests allowed during the rate-limit window.
     */
    [[nodiscard]] int rate_limit_max_requests() const noexcept;

    /**
     * @brief Check whether debug mode is enabled.
     */
    [[nodiscard]] bool debug() const noexcept;

    /**
     * @brief Check whether the app runs in production mode.
     */
    [[nodiscard]] bool is_production() const noexcept;

    /**
     * @brief Check whether the app runs in development mode.
     */
    [[nodiscard]] bool is_development() const noexcept;

  private:
    std::string app_env_{"development"};
    std::string app_root_{"."};
    std::string host_{"0.0.0.0"};
    int port_{8080};
    std::string public_url_{"http://localhost:8080"};
    std::string database_path_{"data/wall.db"};
    std::string log_dir_{"data/logs"};
    int max_message_length_{160};
    int max_username_length_{20};
    int rate_limit_window_sec_{30};
    int rate_limit_max_requests_{10};
    bool debug_{false};
  };

} // namespace wall::config

#endif // WALL_CONFIG_WALLCONFIG_HPP
