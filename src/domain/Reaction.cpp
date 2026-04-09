#include <wall/domain/Reaction.hpp>

#include <utility>

#include <wall/util/Clock.hpp>
#include <wall/util/Ids.hpp>
#include <wall/util/Strings.hpp>

namespace wall::domain
{
  namespace
  {
    std::string normalize_reaction_kind(std::string_view input)
    {
      std::string kind = wall::util::Strings::clean(input);
      kind = wall::util::Strings::limit(kind, 24);

      if (kind.empty())
        return "lightning";

      // For the demo, only allow a very small stable set.
      if (kind == "⚡" || kind == "lightning")
        return "lightning";

      if (kind == "like" || kind == "heart" || kind == "fire")
        return kind;

      return "lightning";
    }
  } // namespace

  Reaction::Reaction(std::string id,
                     std::string message_id,
                     std::string kind,
                     std::int64_t created_at_ms)
      : id_(std::move(id)),
        message_id_(std::move(message_id)),
        kind_(std::move(kind)),
        created_at_ms_(created_at_ms)
  {
  }

  Reaction Reaction::create(std::string_view message_id,
                            std::string_view kind)
  {
    std::string clean_message_id =
        wall::util::Strings::clean(message_id);

    std::string normalized_kind =
        normalize_reaction_kind(kind);

    return Reaction(
        wall::util::Ids::reaction(),
        std::move(clean_message_id),
        std::move(normalized_kind),
        wall::util::Clock::now_ms());
  }

  const std::string &Reaction::id() const noexcept
  {
    return id_;
  }

  const std::string &Reaction::message_id() const noexcept
  {
    return message_id_;
  }

  const std::string &Reaction::kind() const noexcept
  {
    return kind_;
  }

  std::int64_t Reaction::created_at_ms() const noexcept
  {
    return created_at_ms_;
  }

  void Reaction::set_id(std::string value)
  {
    id_ = std::move(value);
  }

  void Reaction::set_message_id(std::string value)
  {
    message_id_ = std::move(value);
  }

  void Reaction::set_kind(std::string value)
  {
    kind_ = std::move(value);
  }

  void Reaction::set_created_at_ms(std::int64_t value) noexcept
  {
    created_at_ms_ = value;
  }

} // namespace wall::domain
