/**
 * @file Stats.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/domain/Stats.hpp>
#include <wall/util/Clock.hpp>

namespace wall::domain
{
  Stats::Stats(std::int64_t total_messages,
               std::int64_t total_reactions,
               std::int64_t online_sessions,
               std::int64_t generated_at_ms)
      : total_messages_(total_messages),
        total_reactions_(total_reactions),
        online_sessions_(online_sessions),
        generated_at_ms_(generated_at_ms)
  {
  }

  Stats Stats::create_empty()
  {
    return Stats(
        0,
        0,
        0,
        wall::util::Clock::now_ms());
  }

  std::int64_t Stats::total_messages() const noexcept
  {
    return total_messages_;
  }

  std::int64_t Stats::total_reactions() const noexcept
  {
    return total_reactions_;
  }

  std::int64_t Stats::online_sessions() const noexcept
  {
    return online_sessions_;
  }

  std::int64_t Stats::generated_at_ms() const noexcept
  {
    return generated_at_ms_;
  }

  void Stats::set_total_messages(std::int64_t value) noexcept
  {
    total_messages_ = value;
  }

  void Stats::set_total_reactions(std::int64_t value) noexcept
  {
    total_reactions_ = value;
  }

  void Stats::set_online_sessions(std::int64_t value) noexcept
  {
    online_sessions_ = value;
  }

  void Stats::set_generated_at_ms(std::int64_t value) noexcept
  {
    generated_at_ms_ = value;
  }

  void Stats::increment_messages() noexcept
  {
    ++total_messages_;
  }

  void Stats::increment_reactions() noexcept
  {
    ++total_reactions_;
  }

} // namespace wall::domain
