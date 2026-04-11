/**
 * @file ApiRoutes.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/http/ApiRoutes.hpp>

#include <algorithm>
#include <cstddef>
#include <string>
#include <string_view>

#include <vix/core.hpp>
#include <vix/json/json.hpp>

#include <wall/json/MessageJson.hpp>
#include <wall/json/StatsJson.hpp>
#include <wall/services/WallService.hpp>
#include <wall/validation/PostMessageInput.hpp>
#include <wall/validation/ReactInput.hpp>
#include <wall/validation/ValidationJson.hpp>
#include <wall/websocket/PresenceHub.hpp>
#include <wall/websocket/WallWebSocket.hpp>

namespace wall::http
{
  namespace
  {
    std::string json_string_or(const vix::json::Json &obj,
                               std::string_view key,
                               std::string fallback = "")
    {
      return vix::json::get_or<std::string>(obj, key, std::move(fallback));
    }

    int parse_int_or(std::string_view text, int fallback)
    {
      if (text.empty())
        return fallback;

      int value = 0;
      bool has_digit = false;

      for (char c : text)
      {
        if (c < '0' || c > '9')
          return fallback;

        has_digit = true;
        value = value * 10 + (c - '0');
      }

      return has_digit ? value : fallback;
    }

    std::string query_value(std::string_view target, std::string_view key)
    {
      const auto qpos = target.find('?');
      if (qpos == std::string_view::npos)
        return "";

      std::string_view query = target.substr(qpos + 1);

      while (!query.empty())
      {
        const auto amp = query.find('&');
        const std::string_view pair =
            (amp == std::string_view::npos) ? query : query.substr(0, amp);

        const auto eq = pair.find('=');
        const std::string_view k =
            (eq == std::string_view::npos) ? pair : pair.substr(0, eq);
        const std::string_view v =
            (eq == std::string_view::npos) ? std::string_view{} : pair.substr(eq + 1);

        if (k == key)
          return std::string(v);

        if (amp == std::string_view::npos)
          break;

        query.remove_prefix(amp + 1);
      }

      return "";
    }

    std::size_t request_limit_or(vix::Request &req, int fallback = 20)
    {
      const std::string raw = query_value(req.target(), "limit");
      const int limit = parse_int_or(raw, fallback);
      const int safe = std::clamp(limit, 1, 100);
      return static_cast<std::size_t>(safe);
    }
  } // namespace

  void ApiRoutes::register_routes(vix::App &app,
                                  wall::services::WallService &wall_service,
                                  wall::websocket::WallWebSocket &wall_websocket,
                                  wall::websocket::PresenceHub &presence_hub)
  {
    app.get("/api/messages",
            [&wall_service](vix::Request &req, vix::Response &res)
            {
              const std::size_t limit = request_limit_or(req, 20);
              const auto messages = wall_service.latest_messages(limit);

              res.json(vix::json::o(
                  "ok", true,
                  "messages", vix::json::to_json(wall::json::MessageJson::to_array(messages))));
            });

    app.post("/api/messages",
             [&wall_service, &wall_websocket](vix::Request &req, vix::Response &res)
             {
               const vix::json::Json &body = req.json();

               wall::validation::PostMessageInput input;
               input.set_username(json_string_or(body, "username"));
               input.set_text(json_string_or(body, "text"));

               const auto result = wall_service.post_message(input);

               if (!result.ok)
               {
                 res.status(400).json(
                     wall::validation::ValidationJson::error_payload(result.errors));
                 return;
               }

               const auto &message = *result.message;

               res.status(201).json(vix::json::o(
                   "ok", true,
                   "message", vix::json::to_json(wall::json::MessageJson::to_json(message))));

               //  wall_websocket.broadcast_message(message);
               //  wall_websocket.broadcast_presence();
               (void)message;
             });

    app.post("/api/reactions",
             [&wall_service, &wall_websocket](vix::Request &req, vix::Response &res)
             {
               const vix::json::Json &body = req.json();

               wall::validation::ReactInput input;
               input.set_message_id(json_string_or(body, "message_id"));
               input.set_kind(json_string_or(body, "kind"));

               const auto result = wall_service.react(input);

               if (!result.ok)
               {
                 res.status(400).json(
                     wall::validation::ValidationJson::error_payload(result.errors));
                 return;
               }

               const auto &reaction = *result.reaction;

               res.status(201).json(vix::json::o(
                   "ok", true,
                   "reaction", vix::json::o("id", reaction.id(), "message_id", reaction.message_id(), "kind", reaction.kind(), "created_at_ms", reaction.created_at_ms())));

               wall_websocket.broadcast_reaction(reaction);
             });

    app.get("/api/stats",
            [&wall_service, &presence_hub](vix::Request &, vix::Response &res)
            {
              const auto stats = wall_service.stats(presence_hub.online_count());

              res.json(vix::json::o(
                  "ok", true,
                  "stats", vix::json::to_json(wall::json::StatsJson::to_json(stats))));
            });
  }

} // namespace wall::http
