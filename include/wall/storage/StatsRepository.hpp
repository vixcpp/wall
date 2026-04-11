/**
 * @file StatsRepository.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_STORAGE_STATSREPOSITORY_HPP
#define WALL_STORAGE_STATSREPOSITORY_HPP

#include <cstdint>
#include <optional>
#include <string>

#include <wall/domain/Stats.hpp>

namespace wall::storage
{
  class Sqlite;

  /**
   * @brief Repository responsible for aggregated wall statistics.
   *
   * This repository reads counts from persisted tables and can also
   * store small metadata values in the `meta` table.
   */
  class StatsRepository
  {
  public:
    /**
     * @brief Construct a repository bound to a SQLite storage.
     */
    explicit StatsRepository(Sqlite &sqlite);

    /**
     * @brief Build a stats snapshot from the database.
     *
     * @param online_sessions Current online sessions count, usually provided
     *        by the in-memory presence tracker.
     */
    wall::domain::Stats snapshot(std::int64_t online_sessions);

    /**
     * @brief Count total messages.
     */
    std::int64_t count_messages();

    /**
     * @brief Count total reactions.
     */
    std::int64_t count_reactions();

    /**
     * @brief Store or replace a meta key/value pair.
     */
    void put_meta(const std::string &key, const std::string &value);

    /**
     * @brief Read a meta value by key.
     */
    std::optional<std::string> get_meta(const std::string &key);

  private:
    Sqlite &sqlite_;
  };

} // namespace wall::storage

#endif // WALL_STORAGE_STATSREPOSITORY_HPP
