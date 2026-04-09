#include <wall/http/ApiRoutes.hpp>

#include <string>

#include <vix/core.hpp>

#include <wall/json/MessageJson.hpp>
#include <wall/json/StatsJson.hpp>
#include <wall/services/WallService.hpp>
#include <wall/validation/PostMessageInput.hpp>
#include <wall/validation/ReactInput.hpp>
#include <wall/validation/ValidationJson.hpp>
#include <wall/websocket/WallWebSocket.hpp>
#include <wall/websocket/PresenceHub.hpp>

namespace wall::http
{
  namespace
  {
    std::string json_string_or(const vix::json::token &obj,
                               std::string_view key,
                               std::string fallback = "")
    {
      if (!obj.is_object())
        return fallback;

      auto object = obj.as_object_ptr();
      if (!object)
        return fallback;

      const auto *value = object->find(key);
      if (!value || !value->is_string())
        return fallback;

      return value->as_string_or(std::move(fallback));
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
              const int limit = req.query_int("limit", 20);
              const std::size_t safe_limit =
                  limit <= 0 ? 20u : static_cast<std::size_t>(limit > 100 ? 100 : limit);

              const auto messages = wall_service.latest_messages(safe_limit);

              res.json(vix::json::obj({
                  "ok",
                  true,
                  "messages",
                  wall::json::MessageJson::to_array(messages),
              }));
            });

    app.post("/api/messages",
             [&wall_service, &wall_websocket](vix::Request &req, vix::Response &res)
             {
               const auto &body = req.json();

               wall::validation::PostMessageInput input;
               input.set_username(json_string_or(body, "username", ""));
               input.set_text(json_string_or(body, "text", ""));

               const auto result = wall_service.post_message(input);

               if (!result.ok)
               {
                 res.status(400).json(
                     wall::validation::ValidationJson::error_payload(result.errors));
                 return;
               }

               const auto &message = *result.message;

               res.status(201).json(vix::json::obj({
                   "ok",
                   true,
                   "message",
                   wall::json::MessageJson::to_json(message),
               }));

               wall_websocket.broadcast_message(message);
               wall_websocket.broadcast_presence();
             });

    app.post("/api/reactions",
             [&wall_service, &wall_websocket](vix::Request &req, vix::Response &res)
             {
               const auto &body = req.json();

               wall::validation::ReactInput input;
               input.set_message_id(json_string_or(body, "message_id", ""));
               input.set_kind(json_string_or(body, "kind", ""));

               const auto result = wall_service.react(input);

               if (!result.ok)
               {
                 res.status(400).json(
                     wall::validation::ValidationJson::error_payload(result.errors));
                 return;
               }

               const auto &reaction = *result.reaction;

               res.status(201).json(vix::json::obj({
                   "ok",
                   true,
                   "reaction",
                   vix::json::obj({
                       "id",
                       reaction.id(),
                       "message_id",
                       reaction.message_id(),
                       "kind",
                       reaction.kind(),
                       "created_at_ms",
                       reaction.created_at_ms(),
                   }),
               }));

               wall_websocket.broadcast_reaction(reaction);
             });

    app.get("/api/stats",
            [&wall_service, &presence_hub](vix::Request &, vix::Response &res)
            {
              const auto stats =
                  wall_service.stats(presence_hub.online_count());

              res.json(vix::json::obj({
                  "ok",
                  true,
                  "stats",
                  wall::json::StatsJson::to_json(stats),
              }));
            });
  }

} // namespace wall::http
