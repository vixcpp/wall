#include <wall/json/EventJson.hpp>

namespace wall::json
{
  namespace
  {
    vix::json::kvs reaction_payload(const wall::domain::Reaction &reaction)
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

    vix::json::kvs presence_payload(std::int64_t online_sessions)
    {
      return vix::json::obj({
          "online_sessions",
          online_sessions,
      });
    }
  } // namespace

  vix::json::kvs EventJson::make(std::string_view type,
                                 const vix::json::token &payload)
  {
    return vix::json::obj({
        "type",
        std::string(type),
        "payload",
        payload,
    });
  }

  vix::json::kvs EventJson::message_created(const wall::domain::Message &message)
  {
    return make("wall.message", MessageJson::to_json(message));
  }

  vix::json::kvs EventJson::reaction_created(const wall::domain::Reaction &reaction)
  {
    return make("wall.reaction", reaction_payload(reaction));
  }

  vix::json::kvs EventJson::presence_updated(std::int64_t online_sessions)
  {
    return make("wall.presence", presence_payload(online_sessions));
  }

  vix::json::kvs EventJson::stats_updated(const wall::domain::Stats &stats)
  {
    return make("wall.stats", StatsJson::to_json(stats));
  }

} // namespace wall::json
