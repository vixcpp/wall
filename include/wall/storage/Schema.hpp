/**
 * @file Schema.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
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
