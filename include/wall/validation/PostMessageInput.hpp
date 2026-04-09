/**
 * @file PostMessageInput.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Input model and validation for posting a wall message.
 */

#ifndef WALL_VALIDATION_POSTMESSAGEINPUT_HPP
#define WALL_VALIDATION_POSTMESSAGEINPUT_HPP

#include <string>
#include <vector>

namespace wall::validation
{
  /**
   * @brief Validation result for a posted wall message.
   */
  struct PostMessageValidationResult
  {
    bool ok{false};
    std::vector<std::string> errors{};
  };

  /**
   * @brief Raw input used to create a wall message.
   */
  class PostMessageInput
  {
  public:
    /**
     * @brief Default constructor.
     */
    PostMessageInput() = default;

    /**
     * @brief Construct input with all fields.
     */
    PostMessageInput(std::string username,
                     std::string text);

    /**
     * @brief Get username.
     */
    const std::string &username() const noexcept;

    /**
     * @brief Get text.
     */
    const std::string &text() const noexcept;

    /**
     * @brief Set username.
     */
    void set_username(std::string value);

    /**
     * @brief Set text.
     */
    void set_text(std::string value);

    /**
     * @brief Validate the input.
     */
    PostMessageValidationResult validate() const;

    /**
     * @brief Check quickly whether the input is valid.
     */
    bool valid() const;

  private:
    std::string username_{};
    std::string text_{};
  };

} // namespace wall::validation

#endif // WALL_VALIDATION_POSTMESSAGEINPUT_HPP
