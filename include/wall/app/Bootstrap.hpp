/**
 * @file Bootstrap.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Application bootstrap for wall.
 */

#ifndef WALL_APP_BOOTSTRAP_HPP
#define WALL_APP_BOOTSTRAP_HPP

#include <wall/app/ServerContext.hpp>
#include <wall/config/WallConfig.hpp>

namespace wall::app
{
  /**
   * @brief Bootstrap entry point for the wall application.
   *
   * This object is responsible for:
   * - building the runtime context
   * - installing HTTP routes
   * - installing WebSocket handlers
   * - starting the server runtime
   */
  class Bootstrap
  {
  public:
    /**
     * @brief Construct the application bootstrap from config.
     */
    explicit Bootstrap(wall::config::WallConfig config);

    /**
     * @brief Access the runtime context.
     */
    wall::app::ServerContext &context() noexcept;

    /**
     * @brief Access the runtime context (const).
     */
    const wall::app::ServerContext &context() const noexcept;

    /**
     * @brief Install routes and realtime handlers.
     */
    void install();

    /**
     * @brief Start the application.
     */
    void run();

  private:
    wall::app::ServerContext context_;
    bool installed_{false};
  };

} // namespace wall::app

#endif // WALL_APP_BOOTSTRAP_HPP
