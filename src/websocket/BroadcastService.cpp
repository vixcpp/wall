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

#include <wall/json/MessageJson.hpp>
#include <wall/json/StatsJson.hpp>
#include <wall/validation/ValidationJson.hpp>

namespace wall::websocket
{
  vix::json::kvs BroadcastService::message_created(
      const wall::domain::Message &message) const
  {
    return wall::json::MessageJson::to_json(message);
  }

  vix::json::kvs BroadcastService::reaction_created(
      const wall::domain::Reaction &reaction) const
  {
    return vix::json::obj({
        "id",
        reaction.id(),
        "message_id",
        reaction.message_id(),
        "kind",
        reaction.kind(),
        "created_at_ms",
        reaction.created_at_ms(),
    });
  }

  vix::json::kvs BroadcastService::presence_updated(
      std::int64_t online_sessions) const
  {
    return vix::json::obj({
        "online_sessions",
        online_sessions,
    });
  }

  vix::json::kvs BroadcastService::stats_updated(
      const wall::domain::Stats &stats) const
  {
    return wall::json::StatsJson::to_json(stats);
  }

  vix::json::kvs BroadcastService::hello(
      const std::string &session_id,
      std::int64_t online_sessions,
      const wall::domain::Stats &stats,
      const std::vector<wall::domain::Message> &latest_messages) const
  {
    return vix::json::obj({
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
    return wall::validation::ValidationJson::error_payload(errors);
  }

} // namespace wall::websocket
