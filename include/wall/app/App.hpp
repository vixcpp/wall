/**
 * @file App.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_APP_APP_HPP
#define WALL_APP_APP_HPP

#include <wall/app/Bootstrap.hpp>
#include <wall/config/WallConfig.hpp>

namespace wall::app
{
  /**
   * @brief High-level facade for the wall application.
   *
   * This is the top-level object used by main().
   */
  class App
  {
  public:
    /**
     * @brief Construct the application from an explicit config.
     */
    explicit App(wall::config::WallConfig config);

    /**
     * @brief Build the application from environment variables.
     */
    static App from_env();

    /**
     * @brief Access the bootstrap object.
     */
    wall::app::Bootstrap &bootstrap() noexcept;

    /**
     * @brief Access the bootstrap object (const).
     */
    const wall::app::Bootstrap &bootstrap() const noexcept;

    /**
     * @brief Start the application.
     */
    void run();

  private:
    wall::app::Bootstrap bootstrap_;
  };

} // namespace wall::app

#endif // WALL_APP_APP_HPP
