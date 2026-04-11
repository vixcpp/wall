/**
 * @file PresenceHub.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/websocket/PresenceHub.hpp>

namespace wall::websocket
{
  wall::domain::Presence PresenceHub::connect()
  {
    std::lock_guard<std::mutex> lock(mutex_);

    wall::domain::Presence presence = wall::domain::Presence::create();
    sessions_[presence.session_id()] = presence;
    return presence;
  }

  bool PresenceHub::disconnect(const std::string &session_id)
  {
    std::lock_guard<std::mutex> lock(mutex_);

    const auto it = sessions_.find(session_id);
    if (it == sessions_.end())
      return false;

    sessions_.erase(it);
    return true;
  }

  bool PresenceHub::touch(const std::string &session_id)
  {
    std::lock_guard<std::mutex> lock(mutex_);

    const auto it = sessions_.find(session_id);
    if (it == sessions_.end())
      return false;

    it->second.touch();
    return true;
  }

  bool PresenceHub::exists(const std::string &session_id) const
  {
    std::lock_guard<std::mutex> lock(mutex_);
    return sessions_.find(session_id) != sessions_.end();
  }

  std::int64_t PresenceHub::online_count() const noexcept
  {
    std::lock_guard<std::mutex> lock(mutex_);
    return static_cast<std::int64_t>(sessions_.size());
  }

  std::vector<wall::domain::Presence> PresenceHub::snapshot() const
  {
    std::lock_guard<std::mutex> lock(mutex_);

    std::vector<wall::domain::Presence> out;
    out.reserve(sessions_.size());

    for (const auto &[id, presence] : sessions_)
    {
      (void)id;
      out.push_back(presence);
    }

    return out;
  }

  void PresenceHub::clear()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    sessions_.clear();
  }

} // namespace wall::websocket
