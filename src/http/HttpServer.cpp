/**
 * @file HttpServer.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/http/HttpServer.hpp>

#include <memory>
#include <vix/core.hpp>
#include <vix/websocket/AttachedRuntime.hpp>

#include <wall/config/WallConfig.hpp>
#include <wall/http/RouteRegistrar.hpp>
#include <wall/services/WallService.hpp>
#include <wall/storage/Sqlite.hpp>
#include <wall/websocket/PresenceHub.hpp>
#include <wall/websocket/WallWebSocket.hpp>

namespace wall::http
{
  HttpServer::HttpServer(const wall::config::WallConfig &config,
                         wall::storage::Sqlite &sqlite,
                         wall::services::WallService &wall_service,
                         wall::websocket::WallWebSocket &wall_websocket,
                         wall::websocket::PresenceHub &presence_hub)
      : config_(config),
        sqlite_(sqlite),
        wall_service_(wall_service),
        wall_websocket_(wall_websocket),
        presence_hub_(presence_hub),
        app_(std::make_unique<vix::App>())
  {
  }

  HttpServer::~HttpServer() = default;

  vix::App &HttpServer::app() noexcept
  {
    return *app_;
  }

  const vix::App &HttpServer::app() const noexcept
  {
    return *app_;
  }

  void HttpServer::install_routes()
  {
    RouteRegistrar::register_routes(
        *app_,
        config_,
        sqlite_,
        wall_service_,
        wall_websocket_,
        presence_hub_);
  }

  void HttpServer::run()
  {
    vix::run_http_and_ws(
        *app_,
        wall_websocket_.server(),
        nullptr,
        config_.port());
  }

} // namespace wall::http
