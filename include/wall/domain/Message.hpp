/**
 * @file Message.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Domain model for a public wall message.
 */

#ifndef WALL_DOMAIN_MESSAGE_HPP
#define WALL_DOMAIN_MESSAGE_HPP

#include <cstdint>
#include <string>
#include <string_view>

namespace wall::domain
{
  /**
   * @brief Public wall message.
   *
   * This is the core domain object of the application.
   */
  class Message
  {
  public:
    /**
     * @brief Default constructor.
     */
    Message() = default;

    /**
     * @brief Construct a message with all fields.
     */
    Message(std::string id,
            std::string username,
            std::string text,
            std::int64_t created_at_ms);

    /**
     * @brief Factory method for creating a new message.
     *
     * This method:
     * - generates an id
     * - normalizes the username
     * - cleans and sanitizes the text
     * - assigns the current timestamp
     */
    static Message create(std::string_view username,
                          std::string_view text);

    /**
     * @brief Get the message id.
     */
    const std::string &id() const noexcept;

    /**
     * @brief Get the username.
     */
    const std::string &username() const noexcept;

    /**
     * @brief Get the message text.
     */
    const std::string &text() const noexcept;

    /**
     * @brief Get the creation timestamp in milliseconds since epoch.
     */
    std::int64_t created_at_ms() const noexcept;

    /**
     * @brief Set the message id.
     */
    void set_id(std::string value);

    /**
     * @brief Set the username.
     */
    void set_username(std::string value);

    /**
     * @brief Set the message text.
     */
    void set_text(std::string value);

    /**
     * @brief Set the creation timestamp in milliseconds since epoch.
     */
    void set_created_at_ms(std::int64_t value) noexcept;

  private:
    std::string id_{};
    std::string username_{};
    std::string text_{};
    std::int64_t created_at_ms_{0};
  };

} // namespace wall::domain

#endif // WALL_DOMAIN_MESSAGE_HPP
