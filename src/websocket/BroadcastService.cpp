/**
 * @file BroadcastService.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/websocket/BroadcastService.hpp>
#include <wall/json/EventJson.hpp>
#include <wall/json/MessageJson.hpp>
#include <wall/json/StatsJson.hpp>
#include <wall/validation/ValidationJson.hpp>
#include <wall/websocket/WallEvents.hpp>

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

  vix::json::kvs BroadcastService::hello(
      const std::string &session_id,
      std::int64_t online_sessions,
      const wall::domain::Stats &stats,
      const std::vector<wall::domain::Message> &latest_messages) const
  {
    return wall::json::EventJson::make(
        WallEvents::hello,
        vix::json::kvs{
            "session_id",
            session_id,
            "online_sessions",
            online_sessions,
            "stats",
            wall::json::StatsJson::to_json(stats),
            "latest_messages",
            wall::json::MessageJson::to_array(latest_messages),
        });
  }

  vix::json::kvs BroadcastService::error(
      const std::vector<std::string> &errors) const
  {
    return wall::json::EventJson::make(
        WallEvents::error,
        wall::validation::ValidationJson::error_payload(errors));
  }

} // namespace wall::websocket
