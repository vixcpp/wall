#include <wall/json/MessageJson.hpp>

namespace wall::json
{
  vix::json::kvs MessageJson::to_json(const wall::domain::Message &message)
  {
    return vix::json::obj({
        "id",
        message.id(),
        "username",
        message.username(),
        "text",
        message.text(),
        "created_at_ms",
        message.created_at_ms(),
    });
  }

  vix::json::array_t MessageJson::to_array(
      const std::vector<wall::domain::Message> &messages)
  {
    vix::json::array_t items;
    items.reserve(messages.size());

    for (const auto &message : messages)
    {
      items.push_back(to_json(message));
    }

    return items;
  }

} // namespace wall::json
