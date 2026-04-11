/**
 * @file Reaction.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_DOMAIN_REACTION_HPP
#define WALL_DOMAIN_REACTION_HPP

#include <cstdint>
#include <string>
#include <string_view>

namespace wall::domain
{
  /**
   * @brief Simple reaction attached to a wall message.
   *
   * Example kinds:
   * - "lightning"
   * - "like"
   *
   * For the first version of wall, we keep reactions intentionally minimal.
   */
  class Reaction
  {
  public:
    /**
     * @brief Default constructor.
     */
    Reaction() = default;

    /**
     * @brief Construct a reaction with all fields.
     */
    Reaction(std::string id,
             std::string message_id,
             std::string kind,
             std::int64_t created_at_ms);

    /**
     * @brief Factory method for creating a new reaction.
     *
     * This method:
     * - generates an id
     * - normalizes the kind
     * - assigns the current timestamp
     */
    static Reaction create(std::string_view message_id,
                           std::string_view kind);

    /**
     * @brief Get the reaction id.
     */
    const std::string &id() const noexcept;

    /**
     * @brief Get the target message id.
     */
    const std::string &message_id() const noexcept;

    /**
     * @brief Get the reaction kind.
     */
    const std::string &kind() const noexcept;

    /**
     * @brief Get the creation timestamp in milliseconds since epoch.
     */
    std::int64_t created_at_ms() const noexcept;

    /**
     * @brief Set the reaction id.
     */
    void set_id(std::string value);

    /**
     * @brief Set the target message id.
     */
    void set_message_id(std::string value);

    /**
     * @brief Set the reaction kind.
     */
    void set_kind(std::string value);

    /**
     * @brief Set the creation timestamp.
     */
    void set_created_at_ms(std::int64_t value) noexcept;

  private:
    std::string id_{};
    std::string message_id_{};
    std::string kind_{};
    std::int64_t created_at_ms_{0};
  };

} // namespace wall::domain

#endif // WALL_DOMAIN_REACTION_HPP
