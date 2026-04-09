/**
 * @file ReactInput.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Input model and validation for reacting to a wall message.
 */

#ifndef WALL_VALIDATION_REACTINPUT_HPP
#define WALL_VALIDATION_REACTINPUT_HPP

#include <string>
#include <vector>

namespace wall::validation
{
  /**
   * @brief Validation result for a wall reaction input.
   */
  struct ReactValidationResult
  {
    bool ok{false};
    std::vector<std::string> errors{};
  };

  /**
   * @brief Raw input used to create a wall reaction.
   */
  class ReactInput
  {
  public:
    /**
     * @brief Default constructor.
     */
    ReactInput() = default;

    /**
     * @brief Construct input with all fields.
     */
    ReactInput(std::string message_id,
               std::string kind);

    /**
     * @brief Get target message id.
     */
    const std::string &message_id() const noexcept;

    /**
     * @brief Get reaction kind.
     */
    const std::string &kind() const noexcept;

    /**
     * @brief Set target message id.
     */
    void set_message_id(std::string value);

    /**
     * @brief Set reaction kind.
     */
    void set_kind(std::string value);

    /**
     * @brief Validate the input.
     */
    ReactValidationResult validate() const;

    /**
     * @brief Check quickly whether the input is valid.
     */
    bool valid() const;

  private:
    std::string message_id_{};
    std::string kind_{};
  };

} // namespace wall::validation

#endif // WALL_VALIDATION_REACTINPUT_HPP
