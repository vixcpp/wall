/**
 * @file StatsRepository.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/storage/StatsRepository.hpp>
#include <wall/storage/Sqlite.hpp>
#include <wall/util/Clock.hpp>

namespace wall::storage
{
  StatsRepository::StatsRepository(Sqlite &sqlite)
      : sqlite_(sqlite)
  {
  }

  wall::domain::Stats StatsRepository::snapshot(std::int64_t online_sessions)
  {
    return wall::domain::Stats(
        count_messages(),
        count_reactions(),
        online_sessions,
        wall::util::Clock::now_ms());
  }

  std::int64_t StatsRepository::count_messages()
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare("SELECT COUNT(*) FROM messages");
    auto rs = stmt->query();

    if (!rs->next())
      return 0;

    return rs->row().getInt64(0);
  }

  std::int64_t StatsRepository::count_reactions()
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare("SELECT COUNT(*) FROM reactions");
    auto rs = stmt->query();

    if (!rs->next())
      return 0;

    return rs->row().getInt64(0);
  }

  void StatsRepository::put_meta(const std::string &key, const std::string &value)
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "INSERT OR REPLACE INTO meta (key, value) "
        "VALUES (?, ?)");

    stmt->bind(1, key);
    stmt->bind(2, value);
    stmt->exec();
  }

  std::optional<std::string> StatsRepository::get_meta(const std::string &key)
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "SELECT value "
        "FROM meta "
        "WHERE key = ? "
        "LIMIT 1");

    stmt->bind(1, key);

    auto rs = stmt->query();
    if (!rs->next())
      return std::nullopt;

    return rs->row().getString(0);
  }

} // namespace wall::storage
