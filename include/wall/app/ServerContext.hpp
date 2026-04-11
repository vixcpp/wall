/**
 * @file ServerContext.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_APP_SERVERCONTEXT_HPP
#define WALL_APP_SERVERCONTEXT_HPP

#include <memory>

#include <vix/config/Config.hpp>
#include <vix/executor/RuntimeExecutor.hpp>

#include <wall/config/WallConfig.hpp>
#include <wall/http/HttpServer.hpp>
#include <wall/services/MessageService.hpp>
#include <wall/services/ModerationService.hpp>
#include <wall/services/ReactionService.hpp>
#include <wall/services/StatsService.hpp>
#include <wall/services/WallService.hpp>
#include <wall/storage/MessageRepository.hpp>
#include <wall/storage/Schema.hpp>
#include <wall/storage/Sqlite.hpp>
#include <wall/storage/StatsRepository.hpp>
#include <wall/websocket/BroadcastService.hpp>
#include <wall/websocket/PresenceHub.hpp>
#include <wall/websocket/WallWebSocket.hpp>

namespace vix::websocket
{
  class Server;
}

namespace wall::app
{
  /**
   * @brief Central application runtime context.
   *
   * This object owns and wires together all core runtime components
   * required by the wall backend.
   */
  class ServerContext
  {
  public:
    /**
     * @brief Construct the full runtime context from configuration.
     */
    explicit ServerContext(wall::config::WallConfig config);

    /**
     * @brief Access application config.
     */
    wall::config::WallConfig &config() noexcept;

    /**
     * @brief Access application config (const).
     */
    const wall::config::WallConfig &config() const noexcept;

    /**
     * @brief Access SQLite storage.
     */
    wall::storage::Sqlite &sqlite() noexcept;

    /**
     * @brief Access message repository.
     */
    wall::storage::MessageRepository &message_repository() noexcept;

    /**
     * @brief Access stats repository.
     */
    wall::storage::StatsRepository &stats_repository() noexcept;

    /**
     * @brief Access message service.
     */
    wall::services::MessageService &message_service() noexcept;

    /**
     * @brief Access reaction service.
     */
    wall::services::ReactionService &reaction_service() noexcept;

    /**
     * @brief Access stats service.
     */
    wall::services::StatsService &stats_service() noexcept;

    /**
     * @brief Access moderation service.
     */
    wall::services::ModerationService &moderation_service() noexcept;

    /**
     * @brief Access central wall service.
     */
    wall::services::WallService &wall_service() noexcept;

    /**
     * @brief Access presence hub.
     */
    wall::websocket::PresenceHub &presence_hub() noexcept;

    /**
     * @brief Access broadcast service.
     */
    wall::websocket::BroadcastService &broadcast_service() noexcept;

    /**
     * @brief Access wall websocket adapter.
     */
    wall::websocket::WallWebSocket &wall_websocket() noexcept;

    /**
     * @brief Access HTTP server.
     */
    wall::http::HttpServer &http_server() noexcept;

  private:
    wall::config::WallConfig config_;

    /**
     * @brief Core Vix configuration used by the WebSocket server.
     *
     * The Vix WebSocket server expects a `vix::config::Config` source.
     * We derive the needed runtime keys from `WallConfig`.
     */
    vix::config::Config core_config_;

    wall::storage::Sqlite sqlite_;
    wall::storage::MessageRepository message_repository_;
    wall::storage::StatsRepository stats_repository_;
    wall::services::MessageService message_service_;
    wall::services::ModerationService moderation_service_;
    wall::services::ReactionService reaction_service_;
    wall::services::StatsService stats_service_;
    wall::services::WallService wall_service_;
    wall::websocket::PresenceHub presence_hub_;
    wall::websocket::BroadcastService broadcast_service_;

    /**
     * @brief Shared runtime executor used by the Vix WebSocket server.
     */
    std::shared_ptr<vix::executor::RuntimeExecutor> ws_executor_;

    /**
     * @brief The underlying Vix WebSocket server used by WallWebSocket.
     *
     * This is owned here so it outlives the adapter.
     */
    std::unique_ptr<vix::websocket::Server> ws_server_;

    /**
     * @brief Wall WebSocket adapter.
     *
     * This is allocated after the Vix WebSocket server is fully constructed.
     */
    std::unique_ptr<wall::websocket::WallWebSocket> wall_websocket_;

    /**
     * @brief HTTP server wrapper.
     *
     * This is allocated after the WebSocket adapter is fully constructed.
     */
    std::unique_ptr<wall::http::HttpServer> http_server_;
  };

} // namespace wall::app

#endif // WALL_APP_SERVERCONTEXT_HPP
