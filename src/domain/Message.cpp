#include <wall/domain/Message.hpp>

#include <utility>

#include <wall/util/Clock.hpp>
#include <wall/util/Env.hpp>
#include <wall/util/Ids.hpp>
#include <wall/util/Strings.hpp>

namespace wall::domain
{
  Message::Message(std::string id,
                   std::string username,
                   std::string text,
                   std::int64_t created_at_ms)
      : id_(std::move(id)),
        username_(std::move(username)),
        text_(std::move(text)),
        created_at_ms_(created_at_ms)
  {
  }

  Message Message::create(std::string_view username,
                          std::string_view text)
  {
    std::string normalized_username =
        wall::util::Strings::normalize_username(username);

    normalized_username =
        wall::util::Strings::limit(
            normalized_username,
            static_cast<std::size_t>(wall::util::Env::max_username_length()));

    std::string clean_text =
        wall::util::Strings::clean(text);

    clean_text =
        wall::util::Strings::sanitize_text(clean_text);

    clean_text =
        wall::util::Strings::limit(
            clean_text,
            static_cast<std::size_t>(wall::util::Env::max_message_length()));

    return Message(
        wall::util::Ids::message(),
        std::move(normalized_username),
        std::move(clean_text),
        wall::util::Clock::now_ms());
  }

  const std::string &Message::id() const noexcept
  {
    return id_;
  }

  const std::string &Message::username() const noexcept
  {
    return username_;
  }

  const std::string &Message::text() const noexcept
  {
    return text_;
  }

  std::int64_t Message::created_at_ms() const noexcept
  {
    return created_at_ms_;
  }

  void Message::set_id(std::string value)
  {
    id_ = std::move(value);
  }

  void Message::set_username(std::string value)
  {
    username_ = std::move(value);
  }

  void Message::set_text(std::string value)
  {
    text_ = std::move(value);
  }

  void Message::set_created_at_ms(std::int64_t value) noexcept
  {
    created_at_ms_ = value;
  }

} // namespace wall::domain
