/**
 * @file RouteRegistrar.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/http/RouteRegistrar.hpp>

#include <vix/core.hpp>

#include <wall/config/WallConfig.hpp>
#include <wall/http/ApiRoutes.hpp>
#include <wall/http/HealthRoutes.hpp>
#include <wall/http/PublicRoutes.hpp>
#include <wall/storage/Sqlite.hpp>
#include <wall/services/WallService.hpp>
#include <wall/websocket/PresenceHub.hpp>
#include <wall/websocket/WallWebSocket.hpp>

namespace wall::http
{
  void RouteRegistrar::register_routes(
      vix::App &app,
      const wall::config::WallConfig &config,
      wall::storage::Sqlite &sqlite,
      wall::services::WallService &wall_service,
      wall::websocket::WallWebSocket &wall_websocket,
      wall::websocket::PresenceHub &presence_hub)
  {
    PublicRoutes::register_routes(app, config);

    ApiRoutes::register_routes(
        app,
        wall_service,
        wall_websocket,
        presence_hub);

    HealthRoutes::register_routes(app, sqlite);
  }

} // namespace wall::http
