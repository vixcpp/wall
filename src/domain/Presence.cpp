/**
 * @file Presence.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/domain/Presence.hpp>

#include <utility>

#include <wall/util/Clock.hpp>
#include <wall/util/Ids.hpp>

namespace wall::domain
{
  Presence::Presence(std::string session_id,
                     std::int64_t connected_at_ms,
                     std::int64_t last_seen_at_ms,
                     bool online)
      : session_id_(std::move(session_id)),
        connected_at_ms_(connected_at_ms),
        last_seen_at_ms_(last_seen_at_ms),
        online_(online)
  {
  }

  Presence Presence::create()
  {
    const std::int64_t now = wall::util::Clock::now_ms();

    return Presence(
        wall::util::Ids::session(),
        now,
        now,
        true);
  }

  void Presence::touch()
  {
    last_seen_at_ms_ = wall::util::Clock::now_ms();
  }

  void Presence::mark_offline() noexcept
  {
    online_ = false;
  }

  void Presence::mark_online() noexcept
  {
    online_ = true;
  }

  const std::string &Presence::session_id() const noexcept
  {
    return session_id_;
  }

  std::int64_t Presence::connected_at_ms() const noexcept
  {
    return connected_at_ms_;
  }

  std::int64_t Presence::last_seen_at_ms() const noexcept
  {
    return last_seen_at_ms_;
  }

  bool Presence::online() const noexcept
  {
    return online_;
  }

  void Presence::set_session_id(std::string value)
  {
    session_id_ = std::move(value);
  }

  void Presence::set_connected_at_ms(std::int64_t value) noexcept
  {
    connected_at_ms_ = value;
  }

  void Presence::set_last_seen_at_ms(std::int64_t value) noexcept
  {
    last_seen_at_ms_ = value;
  }

  void Presence::set_online(bool value) noexcept
  {
    online_ = value;
  }

} // namespace wall::domain
