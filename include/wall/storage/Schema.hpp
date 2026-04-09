/**
 * @file Schema.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Database schema initialization for wall.
 */

#ifndef WALL_STORAGE_SCHEMA_HPP
#define WALL_STORAGE_SCHEMA_HPP

namespace wall::storage
{
  class Sqlite;

  /**
   * @brief Database schema manager for wall.
   *
   * This class is responsible for creating the SQLite tables
   * required by the application.
   */
  class Schema
  {
  public:
    /**
     * @brief Create all required database tables if they do not exist.
     */
    static void ensure(Sqlite &sqlite);
  };

} // namespace wall::storage

#endif // WALL_STORAGE_SCHEMA_HPP
