/**
 * @file Schema.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/storage/Schema.hpp>
#include <wall/storage/Sqlite.hpp>

namespace wall::storage
{
  void Schema::ensure(Sqlite &sqlite)
  {
    sqlite.with_connection(
        [](auto &conn)
        {
          conn->prepare(
                  "CREATE TABLE IF NOT EXISTS messages ("
                  "  id TEXT PRIMARY KEY, "
                  "  username TEXT NOT NULL, "
                  "  text TEXT NOT NULL, "
                  "  created_at_ms INTEGER NOT NULL"
                  ")")
              ->exec();

          conn->prepare(
                  "CREATE INDEX IF NOT EXISTS idx_messages_created_at "
                  "ON messages(created_at_ms DESC)")
              ->exec();

          conn->prepare(
                  "CREATE TABLE IF NOT EXISTS reactions ("
                  "  id TEXT PRIMARY KEY, "
                  "  message_id TEXT NOT NULL, "
                  "  kind TEXT NOT NULL, "
                  "  created_at_ms INTEGER NOT NULL, "
                  "  FOREIGN KEY(message_id) REFERENCES messages(id) ON DELETE CASCADE"
                  ")")
              ->exec();

          conn->prepare(
                  "CREATE INDEX IF NOT EXISTS idx_reactions_message_id "
                  "ON reactions(message_id)")
              ->exec();

          conn->prepare(
                  "CREATE INDEX IF NOT EXISTS idx_reactions_created_at "
                  "ON reactions(created_at_ms DESC)")
              ->exec();

          conn->prepare(
                  "CREATE TABLE IF NOT EXISTS meta ("
                  "  key TEXT PRIMARY KEY, "
                  "  value TEXT NOT NULL"
                  ")")
              ->exec();
        });
  }

} // namespace wall::storage
