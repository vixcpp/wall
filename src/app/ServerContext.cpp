/**
 * @file ServerContext.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/app/ServerContext.hpp>

#include <memory>
#include <utility>

#include <vix/websocket.hpp>

namespace wall::app
{
  ServerContext::ServerContext(wall::config::WallConfig config)
      : config_(std::move(config)),
        core_config_(),
        sqlite_(config_),
        message_repository_(sqlite_),
        stats_repository_(sqlite_),
        message_service_(message_repository_),
        moderation_service_(),
        reaction_service_(sqlite_, message_repository_),
        stats_service_(stats_repository_),
        wall_service_(
            message_service_,
            reaction_service_,
            stats_service_,
            moderation_service_),
        presence_hub_(),
        broadcast_service_(),
        ws_executor_(std::make_shared<vix::executor::RuntimeExecutor>()),
        ws_server_(nullptr),
        wall_websocket_(nullptr),
        http_server_(nullptr)
  {
    core_config_.set("websocket.host", "0.0.0.0");
    core_config_.set("websocket.port", config_.port());

    ws_server_ = std::make_unique<vix::websocket::Server>(core_config_, ws_executor_);

    wall_websocket_ = std::make_unique<wall::websocket::WallWebSocket>(
        *ws_server_,
        wall_service_,
        presence_hub_,
        broadcast_service_);

    http_server_ = std::make_unique<wall::http::HttpServer>(
        config_,
        sqlite_,
        wall_service_,
        *wall_websocket_,
        presence_hub_);

    wall::storage::Schema::ensure(sqlite_);
  }

  wall::config::WallConfig &ServerContext::config() noexcept
  {
    return config_;
  }

  const wall::config::WallConfig &ServerContext::config() const noexcept
  {
    return config_;
  }

  wall::storage::Sqlite &ServerContext::sqlite() noexcept
  {
    return sqlite_;
  }

  wall::storage::MessageRepository &ServerContext::message_repository() noexcept
  {
    return message_repository_;
  }

  wall::storage::StatsRepository &ServerContext::stats_repository() noexcept
  {
    return stats_repository_;
  }

  wall::services::MessageService &ServerContext::message_service() noexcept
  {
    return message_service_;
  }

  wall::services::ReactionService &ServerContext::reaction_service() noexcept
  {
    return reaction_service_;
  }

  wall::services::StatsService &ServerContext::stats_service() noexcept
  {
    return stats_service_;
  }

  wall::services::ModerationService &ServerContext::moderation_service() noexcept
  {
    return moderation_service_;
  }

  wall::services::WallService &ServerContext::wall_service() noexcept
  {
    return wall_service_;
  }

  wall::websocket::PresenceHub &ServerContext::presence_hub() noexcept
  {
    return presence_hub_;
  }

  wall::websocket::BroadcastService &ServerContext::broadcast_service() noexcept
  {
    return broadcast_service_;
  }

  wall::websocket::WallWebSocket &ServerContext::wall_websocket() noexcept
  {
    return *wall_websocket_;
  }

  wall::http::HttpServer &ServerContext::http_server() noexcept
  {
    return *http_server_;
  }

} // namespace wall::app
