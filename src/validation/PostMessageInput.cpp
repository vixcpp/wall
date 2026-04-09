#include <wall/validation/PostMessageInput.hpp>

#include <utility>

#include <wall/util/Env.hpp>
#include <wall/util/Strings.hpp>

namespace wall::validation
{
  PostMessageInput::PostMessageInput(std::string username,
                                     std::string text)
      : username_(std::move(username)),
        text_(std::move(text))
  {
  }

  const std::string &PostMessageInput::username() const noexcept
  {
    return username_;
  }

  const std::string &PostMessageInput::text() const noexcept
  {
    return text_;
  }

  void PostMessageInput::set_username(std::string value)
  {
    username_ = std::move(value);
  }

  void PostMessageInput::set_text(std::string value)
  {
    text_ = std::move(value);
  }

  PostMessageValidationResult PostMessageInput::validate() const
  {
    PostMessageValidationResult result;
    result.ok = false;

    const std::string clean_username =
        wall::util::Strings::clean(username_);

    const std::string normalized_username =
        wall::util::Strings::normalize_username(clean_username);

    const std::string clean_text =
        wall::util::Strings::clean(
            wall::util::Strings::sanitize_text(text_));

    if (wall::util::Strings::is_blank(clean_username))
    {
      result.errors.push_back("username is required");
    }
    else if (normalized_username.empty())
    {
      result.errors.push_back("username contains no valid characters");
    }
    else if (normalized_username.size() >
             static_cast<std::size_t>(wall::util::Env::max_username_length()))
    {
      result.errors.push_back("username is too long");
    }

    if (wall::util::Strings::is_blank(clean_text))
    {
      result.errors.push_back("text is required");
    }
    else if (clean_text.size() >
             static_cast<std::size_t>(wall::util::Env::max_message_length()))
    {
      result.errors.push_back("text is too long");
    }

    result.ok = result.errors.empty();
    return result;
  }

  bool PostMessageInput::valid() const
  {
    return validate().ok;
  }

} // namespace wall::validation
