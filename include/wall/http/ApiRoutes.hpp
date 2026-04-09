/**
 * @file ApiRoutes.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * API HTTP routes for wall.
 */

#ifndef WALL_HTTP_APIROUTES_HPP
#define WALL_HTTP_APIROUTES_HPP

namespace vix
{
  class App;
}

namespace wall::services
{
  class WallService;
}

namespace wall::websocket
{
  class WallWebSocket;
  class PresenceHub;
}

namespace wall::http
{
  /**
   * @brief Register API HTTP routes for wall.
   */
  class ApiRoutes
  {
  public:
    /**
     * @brief Register all API routes.
     */
    static void register_routes(vix::App &app,
                                wall::services::WallService &wall_service,
                                wall::websocket::WallWebSocket &wall_websocket,
                                wall::websocket::PresenceHub &presence_hub);
  };

} // namespace wall::http

#endif // WALL_HTTP_APIROUTES_HPP
