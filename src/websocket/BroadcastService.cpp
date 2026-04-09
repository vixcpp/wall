#include <wall/websocket/BroadcastService.hpp>
#include <wall/json/EventJson.hpp>
#include <wall/validation/ValidationJson.hpp>

namespace wall::websocket
{
  vix::json::kvs BroadcastService::message_created(
      const wall::domain::Message &message) const
  {
    return wall::json::EventJson::message_created(message);
  }

  vix::json::kvs BroadcastService::reaction_created(
      const wall::domain::Reaction &reaction) const
  {
    return wall::json::EventJson::reaction_created(reaction);
  }

  vix::json::kvs BroadcastService::presence_updated(
      std::int64_t online_sessions) const
  {
    return wall::json::EventJson::presence_updated(online_sessions);
  }

  vix::json::kvs BroadcastService::stats_updated(
      const wall::domain::Stats &stats) const
  {
    return wall::json::EventJson::stats_updated(stats);
  }

  vix::json::kvs BroadcastService::error(
      const std::vector<std::string> &errors) const
  {
    return wall::json::EventJson::make(
        "wall.error",
        wall::validation::ValidationJson::error_payload(errors));
  }

} // namespace wall::websocket
