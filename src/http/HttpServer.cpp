#include <wall/http/HttpServer.hpp>

#include <memory>

#include <vix.hpp>

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
    app_->run(config_.port());
  }

} // namespace wall::http
