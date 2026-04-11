/**
 * @file MessageRepository.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/storage/MessageRepository.hpp>

#include <stdexcept>
#include <utility>

#include <wall/storage/Sqlite.hpp>

namespace wall::storage
{
  namespace
  {
    wall::domain::Message hydrate_message(const vix::db::ResultRow &row)
    {
      return wall::domain::Message(
          row.getString(0),
          row.getString(1),
          row.getString(2),
          row.getInt64(3));
    }
  } // namespace

  MessageRepository::MessageRepository(Sqlite &sqlite)
      : sqlite_(sqlite)
  {
  }

  void MessageRepository::insert(const wall::domain::Message &message)
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "INSERT INTO messages (id, username, text, created_at_ms) "
        "VALUES (?, ?, ?, ?)");

    stmt->bind(1, message.id());
    stmt->bind(2, message.username());
    stmt->bind(3, message.text());
    stmt->bind(4, static_cast<std::int64_t>(message.created_at_ms()));
    stmt->exec();
  }

  std::optional<wall::domain::Message>
  MessageRepository::find_by_id(const std::string &id)
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "SELECT id, username, text, created_at_ms "
        "FROM messages "
        "WHERE id = ? "
        "LIMIT 1");

    stmt->bind(1, id);

    auto rs = stmt->query();
    if (!rs->next())
      return std::nullopt;

    return hydrate_message(rs->row());
  }

  bool MessageRepository::exists(const std::string &id)
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "SELECT 1 "
        "FROM messages "
        "WHERE id = ? "
        "LIMIT 1");

    stmt->bind(1, id);

    auto rs = stmt->query();
    return rs->next();
  }

  std::vector<wall::domain::Message>
  MessageRepository::latest(std::size_t limit)
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "SELECT id, username, text, created_at_ms "
        "FROM messages "
        "ORDER BY created_at_ms DESC "
        "LIMIT ?");

    stmt->bind(1, static_cast<std::int64_t>(limit));

    auto rs = stmt->query();

    std::vector<wall::domain::Message> out;
    out.reserve(limit);

    while (rs->next())
    {
      out.push_back(hydrate_message(rs->row()));
    }

    return out;
  }

  std::int64_t MessageRepository::count()
  {
    auto conn = sqlite_.connect();

    auto stmt = conn->prepare(
        "SELECT COUNT(*) FROM messages");

    auto rs = stmt->query();
    if (!rs->next())
      return 0;

    return rs->row().getInt64(0);
  }

} // namespace wall::storage
