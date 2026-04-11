/**
 * @file RouteRegistrar.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_HTTP_ROUTEREGISTRAR_HPP
#define WALL_HTTP_ROUTEREGISTRAR_HPP

namespace vix
{
  class App;
}

namespace wall::config
{
  class WallConfig;
}

namespace wall::services
{
  class WallService;
}

namespace wall::storage
{
  class Sqlite;
}

namespace wall::websocket
{
  class PresenceHub;
  class WallWebSocket;
}

namespace wall::http
{
  /**
   * @brief Central route registration entry point for wall.
   */
  class RouteRegistrar
  {
  public:
    /**
     * @brief Register all HTTP routes for wall.
     */
    static void register_routes(vix::App &app,
                                const wall::config::WallConfig &config,
                                wall::storage::Sqlite &sqlite,
                                wall::services::WallService &wall_service,
                                wall::websocket::WallWebSocket &wall_websocket,
                                wall::websocket::PresenceHub &presence_hub);
  };

} // namespace wall::http

#endif // WALL_HTTP_ROUTEREGISTRAR_HPP
