/**
 * @file PublicRoutes.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
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

    app.get("/app.js",
            [](vix::Request &, vix::Response &res)
            {
              res.file("static/app.js");
            });

    app.get("/style.css",
            [](vix::Request &, vix::Response &res)
            {
              res.file("static/style.css");
            });

    app.get("/health",
            [](vix::Request &, vix::Response &res)
            {
              res.json(vix::json::o(
                  "ok", true,
                  "service", "wall",
                  "status", "healthy"));
            });

    app.get("/about",
            [&config](vix::Request &, vix::Response &res)
            {
              res.json(vix::json::o(
                  "name", "wall",
                  "runtime", "Vix.cpp",
                  "environment", config.app_env(),
                  "debug", config.debug()));
            });
  }
} // namespace wall::http
