/**
 * @file Presence.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_DOMAIN_PRESENCE_HPP
#define WALL_DOMAIN_PRESENCE_HPP

#include <cstdint>
#include <string>
#include <string_view>

namespace wall::domain
{
  /**
   * @brief Represents a connected public wall session.
   *
   * This model is intentionally minimal.
   * It is mainly used for live presence tracking.
   */
  class Presence
  {
  public:
    /**
     * @brief Default constructor.
     */
    Presence() = default;

    /**
     * @brief Construct a presence object with all fields.
     */
    Presence(std::string session_id,
             std::int64_t connected_at_ms,
             std::int64_t last_seen_at_ms,
             bool online);

    /**
     * @brief Create a new online presence session.
     *
     * This method:
     * - generates a session id
     * - sets connected_at_ms
     * - sets last_seen_at_ms
     * - marks the session as online
     */
    static Presence create();

    /**
     * @brief Mark this session as seen "now".
     */
    void touch();

    /**
     * @brief Mark this session as offline.
     */
    void mark_offline() noexcept;

    /**
     * @brief Mark this session as online.
     */
    void mark_online() noexcept;

    /**
     * @brief Get the session id.
     */
    const std::string &session_id() const noexcept;

    /**
     * @brief Get the connection timestamp in milliseconds since epoch.
     */
    std::int64_t connected_at_ms() const noexcept;

    /**
     * @brief Get the last activity timestamp in milliseconds since epoch.
     */
    std::int64_t last_seen_at_ms() const noexcept;

    /**
     * @brief Check whether the session is online.
     */
    bool online() const noexcept;

    /**
     * @brief Set the session id.
     */
    void set_session_id(std::string value);

    /**
     * @brief Set the connection timestamp.
     */
    void set_connected_at_ms(std::int64_t value) noexcept;

    /**
     * @brief Set the last activity timestamp.
     */
    void set_last_seen_at_ms(std::int64_t value) noexcept;

    /**
     * @brief Set the online state.
     */
    void set_online(bool value) noexcept;

  private:
    std::string session_id_{};
    std::int64_t connected_at_ms_{0};
    std::int64_t last_seen_at_ms_{0};
    bool online_{false};
  };

} // namespace wall::domain

#endif // WALL_DOMAIN_PRESENCE_HPP
