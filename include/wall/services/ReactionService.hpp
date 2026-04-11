/**
 * @file ReactionService.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_SERVICES_REACTIONSERVICE_HPP
#define WALL_SERVICES_REACTIONSERVICE_HPP

#include <optional>
#include <string>
#include <vector>

#include <wall/domain/Reaction.hpp>
#include <wall/storage/MessageRepository.hpp>
#include <wall/storage/Sqlite.hpp>
#include <wall/validation/ReactInput.hpp>

namespace wall::services
{
  /**
   * @brief Result returned when creating a reaction.
   */
  struct ReactResult
  {
    bool ok{false};
    std::optional<wall::domain::Reaction> reaction{};
    std::vector<std::string> errors{};
  };

  /**
   * @brief Application service responsible for wall reactions.
   */
  class ReactionService
  {
  public:
    /**
     * @brief Construct a reaction service.
     */
    ReactionService(wall::storage::Sqlite &sqlite,
                    wall::storage::MessageRepository &message_repository);

    /**
     * @brief Validate, create and persist a new reaction.
     */
    ReactResult react(const wall::validation::ReactInput &input);

    /**
     * @brief Count total persisted reactions.
     */
    std::int64_t count();

  private:
    wall::storage::Sqlite &sqlite_;
    wall::storage::MessageRepository &message_repository_;
  };

} // namespace wall::services

#endif // WALL_SERVICES_REACTIONSERVICE_HPP
