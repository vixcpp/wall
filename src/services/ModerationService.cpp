/**
 * @file ModerationService.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/services/ModerationService.hpp>
#include <utility>
#include <wall/util/Strings.hpp>
#include <vix/utils/String.hpp>

namespace wall::services
{
  ModerationService::ModerationService()
      : blocked_terms_{
            "spam",
            "scam",
            "fraud"}
  {
  }

  ModerationService::ModerationService(std::vector<std::string> blocked_terms)
      : blocked_terms_(std::move(blocked_terms))
  {
  }

  ModerationResult ModerationService::moderate_message(std::string_view text) const
  {
    ModerationResult result;
    result.ok = false;

    const std::string clean_text =
        wall::util::Strings::clean(
            wall::util::Strings::sanitize_text(text));

    if (wall::util::Strings::is_blank(clean_text))
    {
      result.errors.push_back("message is empty");
    }

    if (contains_blocked_term(clean_text))
    {
      result.errors.push_back("message contains blocked content");
    }

    if (has_excessive_repetition(clean_text))
    {
      result.errors.push_back("message looks like spam");
    }

    result.ok = result.errors.empty();
    return result;
  }

  bool ModerationService::allow_message(std::string_view text) const
  {
    return moderate_message(text).ok;
  }

  const std::vector<std::string> &ModerationService::blocked_terms() const noexcept
  {
    return blocked_terms_;
  }

  bool ModerationService::contains_blocked_term(std::string_view text) const
  {
    const std::string haystack =
        vix::utils::to_lower(std::string(text));

    for (const auto &term : blocked_terms_)
    {
      const std::string needle =
          vix::utils::to_lower(term);

      if (!needle.empty() && haystack.find(needle) != std::string::npos)
      {
        return true;
      }
    }

    return false;
  }

  bool ModerationService::has_excessive_repetition(std::string_view text) noexcept
  {
    if (text.empty())
      return false;

    char previous = '\0';
    int run = 0;

    for (char c : text)
    {
      if (c == previous)
      {
        ++run;
      }
      else
      {
        previous = c;
        run = 1;
      }

      if (run >= 12)
      {
        return true;
      }
    }

    return false;
  }

} // namespace wall::services
