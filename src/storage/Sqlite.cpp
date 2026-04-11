/**
 * @file Sqlite.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/storage/Sqlite.hpp>

#include <utility>

namespace wall::storage
{
  Sqlite::Sqlite(std::string path)
      : path_(std::move(path)),
        db_(vix::db::Database::sqlite(path_))
  {
  }

  Sqlite::Sqlite(const wall::config::WallConfig &config)
      : Sqlite(config.database_path())
  {
  }

  const std::string &Sqlite::path() const noexcept
  {
    return path_;
  }

  vix::db::Database &Sqlite::db() noexcept
  {
    return db_;
  }

  const vix::db::Database &Sqlite::db() const noexcept
  {
    return db_;
  }

  vix::db::ConnectionPool &Sqlite::pool() noexcept
  {
    return db_.pool();
  }

  const vix::db::ConnectionPool &Sqlite::pool() const noexcept
  {
    return db_.pool();
  }

  vix::db::PooledConn Sqlite::connect()
  {
    return vix::db::PooledConn(pool());
  }

} // namespace wall::storage
