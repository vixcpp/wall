/**
 * @file MessageService.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#ifndef WALL_SERVICES_MESSAGESERVICE_HPP
#define WALL_SERVICES_MESSAGESERVICE_HPP

#include <optional>
#include <string>
#include <vector>

#include <wall/domain/Message.hpp>
#include <wall/storage/MessageRepository.hpp>
#include <wall/validation/PostMessageInput.hpp>

namespace wall::services
{
  /**
   * @brief Result returned when posting a message.
   */
  struct PostMessageResult
  {
    bool ok{false};
    std::optional<wall::domain::Message> message{};
    std::vector<std::string> errors{};
  };

  /**
   * @brief Application service responsible for message operations.
   */
  class MessageService
  {
  public:
    /**
     * @brief Construct a message service.
     */
    explicit MessageService(wall::storage::MessageRepository &repository);

    /**
     * @brief Validate, create and persist a new message.
     */
    PostMessageResult post(const wall::validation::PostMessageInput &input);

    /**
     * @brief Return the latest persisted messages.
     */
    std::vector<wall::domain::Message> latest(std::size_t limit);

    /**
     * @brief Find a message by id.
     */
    std::optional<wall::domain::Message> find_by_id(const std::string &id);

    /**
     * @brief Count total persisted messages.
     */
    std::int64_t count();

  private:
    wall::storage::MessageRepository &repository_;
  };

} // namespace wall::services

#endif // WALL_SERVICES_MESSAGESERVICE_HPP
