/**
 * @file Strings.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/util/Strings.hpp>
#include <vix/utils/String.hpp>

#include <algorithm>
#include <cctype>

namespace wall::util
{
  using namespace vix::utils;

  std::string Strings::clean(std::string_view input)
  {
    // trim + collapse simple spaces
    std::string s = trim(std::string(input));

    std::string out;
    out.reserve(s.size());

    bool last_space = false;

    for (char c : s)
    {
      if (c == ' ')
      {
        if (!last_space)
        {
          out.push_back(c);
          last_space = true;
        }
      }
      else
      {
        out.push_back(c);
        last_space = false;
      }
    }

    return out;
  }

  std::string Strings::normalize_username(std::string_view input)
  {
    std::string s = to_lower(trim(std::string(input)));

    std::string out;
    out.reserve(s.size());

    for (char c : s)
    {
      // allow: a-z, 0-9, _, -
      if ((c >= 'a' && c <= 'z') ||
          (c >= '0' && c <= '9') ||
          c == '_' || c == '-')
      {
        out.push_back(c);
      }
    }

    if (out.empty())
      return "anonymous";

    return out;
  }

  std::string Strings::limit(std::string_view input, std::size_t max_len)
  {
    if (input.size() <= max_len)
      return std::string(input);

    return std::string(input.substr(0, max_len));
  }

  bool Strings::is_blank(std::string_view input) noexcept
  {
    for (char c : input)
    {
      if (!std::isspace(static_cast<unsigned char>(c)))
        return false;
    }
    return true;
  }

  std::string Strings::sanitize_text(std::string_view input)
  {
    std::string out;
    out.reserve(input.size());

    for (char c : input)
    {
      // remove control characters except newline
      if ((c >= 32 && c <= 126) || c == '\n')
      {
        out.push_back(c);
      }
    }

    return out;
  }

} // namespace wall::util
