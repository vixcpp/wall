#include <wall/validation/ReactInput.hpp>
#include <utility>
#include <wall/util/Strings.hpp>

namespace wall::validation
{
  namespace
  {
    bool is_allowed_reaction_kind(const std::string &kind) noexcept
    {
      return kind == "⚡" ||
             kind == "lightning" ||
             kind == "like" ||
             kind == "heart" ||
             kind == "fire";
    }
  } // namespace

  ReactInput::ReactInput(std::string message_id,
                         std::string kind)
      : message_id_(std::move(message_id)),
        kind_(std::move(kind))
  {
  }

  const std::string &ReactInput::message_id() const noexcept
  {
    return message_id_;
  }

  const std::string &ReactInput::kind() const noexcept
  {
    return kind_;
  }

  void ReactInput::set_message_id(std::string value)
  {
    message_id_ = std::move(value);
  }

  void ReactInput::set_kind(std::string value)
  {
    kind_ = std::move(value);
  }

  ReactValidationResult ReactInput::validate() const
  {
    ReactValidationResult result;
    result.ok = false;

    const std::string clean_message_id =
        wall::util::Strings::clean(message_id_);

    const std::string clean_kind =
        wall::util::Strings::clean(kind_);

    if (wall::util::Strings::is_blank(clean_message_id))
    {
      result.errors.push_back("message_id is required");
    }

    if (wall::util::Strings::is_blank(clean_kind))
    {
      result.errors.push_back("kind is required");
    }
    else if (clean_kind.size() > 24)
    {
      result.errors.push_back("kind is too long");
    }
    else if (!is_allowed_reaction_kind(clean_kind))
    {
      result.errors.push_back("kind is not allowed");
    }

    result.ok = result.errors.empty();
    return result;
  }

  bool ReactInput::valid() const
  {
    return validate().ok;
  }

} // namespace wall::validation
