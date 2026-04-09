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
   */
  class WallConfig
  {
  public:
    /**
     * @brief Build a config instance from environment variables.
     */
    static WallConfig from_env();

    /**
     * @brief Default constructor.
     */
    WallConfig() = default;

    /**
     * @brief Full constructor.
     */
    WallConfig(std::string app_env,
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
    const std::string &app_env() const noexcept;

    /**
     * @brief Get the HTTP host.
     */
    const std::string &host() const noexcept;

    /**
     * @brief Get the HTTP port.
     */
    int port() const noexcept;

    /**
     * @brief Get the public base URL.
     */
    const std::string &public_url() const noexcept;

    /**
     * @brief Get the SQLite database path.
     */
    const std::string &database_path() const noexcept;

    /**
     * @brief Get the log directory.
     */
    const std::string &log_dir() const noexcept;

    /**
     * @brief Get the maximum allowed message length.
     */
    int max_message_length() const noexcept;

    /**
     * @brief Get the maximum allowed username length.
     */
    int max_username_length() const noexcept;

    /**
     * @brief Get the rate-limit window in seconds.
     */
    int rate_limit_window_sec() const noexcept;

    /**
     * @brief Get the max requests allowed during the rate-limit window.
     */
    int rate_limit_max_requests() const noexcept;

    /**
     * @brief Check whether debug mode is enabled.
     */
    bool debug() const noexcept;

    /**
     * @brief Check whether the app runs in production mode.
     */
    bool is_production() const noexcept;

    /**
     * @brief Check whether the app runs in development mode.
     */
    bool is_development() const noexcept;

  private:
    std::string app_env_{"development"};
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
