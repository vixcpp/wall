/**
 * @file PublicRoutes.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_HTTP_PUBLICROUTES_HPP
#define WALL_HTTP_PUBLICROUTES_HPP

namespace vix
{
  class App;
}

namespace wall::config
{
  class WallConfig;
}

namespace wall::http
{
  /**
   * @brief Register public HTTP routes for wall.
   *
   * These routes expose the public landing page and lightweight
   * public informational endpoints.
   */
  class PublicRoutes
  {
  public:
    /**
     * @brief Register all public routes.
     */
    static void register_routes(vix::App &app,
                                const wall::config::WallConfig &config);
  };

} // namespace wall::http

#endif // WALL_HTTP_PUBLICROUTES_HPP
