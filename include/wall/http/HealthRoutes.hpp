/**
 * @file HealthRoutes.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Health and readiness HTTP routes for wall.
 */

#ifndef WALL_HTTP_HEALTHROUTES_HPP
#define WALL_HTTP_HEALTHROUTES_HPP

namespace vix
{
  class App;
}

namespace wall::storage
{
  class Sqlite;
}

namespace wall::http
{
  /**
   * @brief Register health and readiness routes for wall.
   */
  class HealthRoutes
  {
  public:
    /**
     * @brief Register all health-related routes.
     */
    static void register_routes(vix::App &app,
                                wall::storage::Sqlite &sqlite);
  };

} // namespace wall::http

#endif // WALL_HTTP_HEALTHROUTES_HPP
