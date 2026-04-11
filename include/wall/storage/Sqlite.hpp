/**
 * @file Sqlite.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_STORAGE_SQLITE_HPP
#define WALL_STORAGE_SQLITE_HPP

#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include <vix/db/Database.hpp>
#include <wall/config/WallConfig.hpp>

namespace wall::storage
{
  /**
   * @brief Small SQLite facade for wall.
   *
   * This class owns the Vix database object and provides convenient
   * access to the underlying connection pool.
   *
   * It also serializes database access to avoid unsafe concurrent
   * operations against the same SQLite storage from HTTP and WebSocket
   * execution paths.
   */
  class Sqlite
  {
  public:
    /**
     * @brief Construct from a database file path.
     */
    explicit Sqlite(std::string path);

    /**
     * @brief Construct from wall runtime config.
     */
    explicit Sqlite(const wall::config::WallConfig &config);

    /**
     * @brief Get the configured SQLite file path.
     */
    const std::string &path() const noexcept;

    /**
     * @brief Access the underlying Vix database facade.
     */
    vix::db::Database &db() noexcept;

    /**
     * @brief Access the underlying Vix database facade (const).
     */
    const vix::db::Database &db() const noexcept;

    /**
     * @brief Access the underlying connection pool.
     */
    vix::db::ConnectionPool &pool() noexcept;

    /**
     * @brief Access the underlying connection pool (const).
     */
    const vix::db::ConnectionPool &pool() const noexcept;

    /**
     * @brief Acquire a pooled connection.
     *
     * This function serializes the acquisition step.
     * For full query safety, prefer @ref with_connection so the whole
     * database operation stays protected by the same mutex.
     */
    vix::db::PooledConn connect();

    /**
     * @brief Execute a database operation under a global SQLite lock.
     *
     * This helper is the preferred way to run queries when the wall
     * application may access SQLite concurrently from multiple threads.
     *
     * Example:
     * @code
     * auto count = sqlite.with_connection([](auto &conn)
     * {
     *   auto stmt = conn->prepare("SELECT COUNT(*) FROM messages");
     *   auto rs = stmt->query();
     *   return rs->next() ? rs->row().getInt64(0) : 0;
     * });
     * @endcode
     *
     * @tparam Fn Callable type receiving a pooled connection.
     * @param fn Database operation to execute.
     *
     * @return The value returned by the callable.
     */
    template <typename Fn>
    decltype(auto) with_connection(Fn &&fn)
    {
      std::lock_guard<std::mutex> lock(mutex_);
      auto conn = vix::db::PooledConn(pool());
      return std::forward<Fn>(fn)(conn);
    }

  private:
    /**
     * @brief SQLite database file path.
     */
    std::string path_{};

    /**
     * @brief Owned Vix database facade.
     */
    vix::db::Database db_;

    /**
     * @brief Global mutex protecting SQLite operations.
     *
     * SQLite is much safer here when all wall database access is
     * serialized from this facade.
     */
    mutable std::mutex mutex_{};
  };

} // namespace wall::storage

#endif // WALL_STORAGE_SQLITE_HPP
