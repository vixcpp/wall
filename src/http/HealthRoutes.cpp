/**
 * @file HealthRoutes.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/http/HealthRoutes.hpp>
#include <vix/core.hpp>
#include <wall/storage/Sqlite.hpp>

#include <exception>

namespace wall::http
{
  void HealthRoutes::register_routes(vix::App &app,
                                     wall::storage::Sqlite &sqlite)
  {
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

    app.get("/live",
            [](vix::Request &, vix::Response &res)
            {
              res.json(vix::json::obj({
                  "ok",
                  true,
                  "service",
                  "wall",
                  "status",
                  "alive",
              }));
            });

    app.get("/ready",
            [&sqlite](vix::Request &, vix::Response &res)
            {
              try
              {
                auto conn = sqlite.connect();
                auto stmt = conn->prepare("SELECT 1");
                auto rs = stmt->query();

                const bool ok = rs->next();

                if (!ok)
                {
                  res.status(503).json(vix::json::obj({
                      "ok",
                      false,
                      "service",
                      "wall",
                      "status",
                      "not_ready",
                      "database",
                      "query_failed",
                  }));
                  return;
                }

                res.json(vix::json::obj({
                    "ok",
                    true,
                    "service",
                    "wall",
                    "status",
                    "ready",
                    "database",
                    "ok",
                }));
              }
              catch (const std::exception &e)
              {
                res.status(503).json(vix::json::obj({
                    "ok",
                    false,
                    "service",
                    "wall",
                    "status",
                    "not_ready",
                    "database",
                    "error",
                    "message",
                    std::string(e.what()),
                }));
              }
            });
  }

} // namespace wall::http
