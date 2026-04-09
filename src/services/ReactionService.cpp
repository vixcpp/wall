#include <wall/services/ReactionService.hpp>
#include <utility>

namespace wall::services
{
  ReactionService::ReactionService(
      wall::storage::Sqlite &sqlite,
      wall::storage::MessageRepository &message_repository)
      : sqlite_(sqlite),
        message_repository_(message_repository)
  {
  }

  ReactResult ReactionService::react(const wall::validation::ReactInput &input)
  {
    const auto validation = input.validate();

    if (!validation.ok)
    {
      return ReactResult{
          .ok = false,
          .reaction = std::nullopt,
          .errors = validation.errors};
    }

    if (!message_repository_.exists(input.message_id()))
    {
      return ReactResult{
          .ok = false,
          .reaction = std::nullopt,
          .errors = {"message not found"}};
    }

    wall::domain::Reaction reaction =
        wall::domain::Reaction::create(
            input.message_id(),
            input.kind());

    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "INSERT INTO reactions (id, message_id, kind, created_at_ms) "
        "VALUES (?, ?, ?, ?)");

    stmt->bind(1, reaction.id());
    stmt->bind(2, reaction.message_id());
    stmt->bind(3, reaction.kind());
    stmt->bind(4, static_cast<std::int64_t>(reaction.created_at_ms()));
    stmt->exec();

    return ReactResult{
        .ok = true,
        .reaction = std::move(reaction),
        .errors = {}};
  }

  std::int64_t ReactionService::count()
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare("SELECT COUNT(*) FROM reactions");
    auto rs = stmt->query();

    if (!rs->next())
      return 0;

    return rs->row().getInt64(0);
  }

} // namespace wall::services
