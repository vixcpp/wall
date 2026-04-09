#include <wall/http/PublicRoutes.hpp>
#include <wall/config/WallConfig.hpp>
#include <vix/core.hpp>

namespace wall::http
{
  void PublicRoutes::register_routes(vix::App &app,
                                     const wall::config::WallConfig &config)
  {
    app.get("/",
            [](vix::Request &, vix::Response &res)
            {
              res.file("static/index.html");
            });

    app.get("/health",
            [](vix::Request &, vix::Response &res)
            {
              res.json(vix::json::obj({
                  "ok",
                  true,
                  "service",
                  "wall",
                  "status",
                  "healthy",
              }));
            });

    app.get("/about",
            [&config](vix::Request &, vix::Response &res)
            {
              res.json(vix::json::obj({
                  "name",
                  "wall",
                  "runtime",
                  "Vix.cpp",
                  "environment",
                  config.app_env(),
                  "debug",
                  config.debug(),
              }));
            });
  }

} // namespace wall::http
