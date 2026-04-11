/**
 * @file HttpServer.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_HTTP_HTTPSERVER_HPP
#define WALL_HTTP_HTTPSERVER_HPP

#include <memory>

namespace vix
{
  class App;
}

namespace wall::config
{
  class WallConfig;
}

namespace wall::storage
{
  class Sqlite;
}

namespace wall::services
{
  class WallService;
}

namespace wall::websocket
{
  class PresenceHub;
  class WallWebSocket;
}

namespace wall::http
{
  /**
   * @brief Small wrapper around the Vix HTTP app.
   *
   * Responsibilities:
   * - own the HTTP app instance
   * - register routes
   * - start listening
   */
  class HttpServer
  {
  public:
    /**
     * @brief Construct the HTTP server wrapper.
     */
    HttpServer(const wall::config::WallConfig &config,
               wall::storage::Sqlite &sqlite,
               wall::services::WallService &wall_service,
               wall::websocket::WallWebSocket &wall_websocket,
               wall::websocket::PresenceHub &presence_hub);

    /**
     * @brief Destroy the HTTP server wrapper.
     *
     * Defined in the implementation file so `vix::App` is complete
     * when the unique pointer is destroyed.
     */
    ~HttpServer();

    HttpServer(const HttpServer &) = delete;
    HttpServer &operator=(const HttpServer &) = delete;
    HttpServer(HttpServer &&) noexcept = default;
    HttpServer &operator=(HttpServer &&) noexcept = default;

    /**
     * @brief Access the underlying Vix app.
     */
    vix::App &app() noexcept;

    /**
     * @brief Access the underlying Vix app (const).
     */
    const vix::App &app() const noexcept;

    /**
     * @brief Register all HTTP routes.
     */
    void install_routes();

    /**
     * @brief Start the HTTP server.
     *
     * Exact listen behavior depends on the Vix App implementation.
     */
    void run();

  private:
    const wall::config::WallConfig &config_;
    wall::storage::Sqlite &sqlite_;
    wall::services::WallService &wall_service_;
    wall::websocket::WallWebSocket &wall_websocket_;
    wall::websocket::PresenceHub &presence_hub_;
    std::unique_ptr<vix::App> app_;
  };

} // namespace wall::http

#endif // WALL_HTTP_HTTPSERVER_HPP
