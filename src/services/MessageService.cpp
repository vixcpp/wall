#include <wall/services/MessageService.hpp>
#include <wall/domain/Message.hpp>

namespace wall::services
{
  MessageService::MessageService(wall::storage::MessageRepository &repository)
      : repository_(repository)
  {
  }

  PostMessageResult MessageService::post(const wall::validation::PostMessageInput &input)
  {
    const auto validation = input.validate();

    if (!validation.ok)
    {
      return PostMessageResult{
          .ok = false,
          .message = std::nullopt,
          .errors = validation.errors};
    }

    wall::domain::Message message =
        wall::domain::Message::create(
            input.username(),
            input.text());

    repository_.insert(message);

    return PostMessageResult{
        .ok = true,
        .message = std::move(message),
        .errors = {}};
  }

  std::vector<wall::domain::Message> MessageService::latest(std::size_t limit)
  {
    return repository_.latest(limit);
  }

  std::optional<wall::domain::Message>
  MessageService::find_by_id(const std::string &id)
  {
    return repository_.find_by_id(id);
  }

  std::int64_t MessageService::count()
  {
    return repository_.count();
  }

} // namespace wall::services
