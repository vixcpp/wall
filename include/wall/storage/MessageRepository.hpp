/**
 * @file MessageRepository.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_STORAGE_MESSAGEREPOSITORY_HPP
#define WALL_STORAGE_MESSAGEREPOSITORY_HPP

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include <wall/domain/Message.hpp>

namespace wall::storage
{
  class Sqlite;

  /**
   * @brief Repository responsible for wall message persistence.
   */
  class MessageRepository
  {
  public:
    /**
     * @brief Construct a repository bound to a SQLite storage.
     */
    explicit MessageRepository(Sqlite &sqlite);

    /**
     * @brief Insert a new message.
     */
    void insert(const wall::domain::Message &message);

    /**
     * @brief Find a message by its id.
     */
    std::optional<wall::domain::Message> find_by_id(const std::string &id);

    /**
     * @brief Check whether a message exists.
     */
    bool exists(const std::string &id);

    /**
     * @brief Return the latest messages ordered by creation time descending.
     *
     * @param limit Maximum number of messages to return.
     */
    std::vector<wall::domain::Message> latest(std::size_t limit);

    /**
     * @brief Count total persisted messages.
     */
    std::int64_t count();

  private:
    Sqlite &sqlite_;
  };

} // namespace wall::storage

#endif // WALL_STORAGE_MESSAGEREPOSITORY_HPP
