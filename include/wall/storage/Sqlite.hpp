/**
 * @file Sqlite.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * SQLite storage wrapper for wall.
 */

#ifndef WALL_STORAGE_SQLITE_HPP
#define WALL_STORAGE_SQLITE_HPP

#include <memory>
#include <string>

#include <vix/db/Database.hpp>
#include <wall/config/WallConfig.hpp>

namespace wall::storage
{
  /**
   * @brief Small SQLite facade for wall.
   *
   * This class owns the Vix database object and provides convenient
   * access to the underlying connection pool.
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
     * This is the preferred way to perform queries.
     */
    vix::db::PooledConn connect();

  private:
    std::string path_{};
    vix::db::Database db_;
  };

} // namespace wall::storage

#endif // WALL_STORAGE_SQLITE_HPP
