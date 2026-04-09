/**
 * @file ModerationService.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Basic moderation helpers for wall.
 */

#ifndef WALL_SERVICES_MODERATIONSERVICE_HPP
#define WALL_SERVICES_MODERATIONSERVICE_HPP

#include <string>
#include <string_view>
#include <vector>

namespace wall::services
{
  /**
   * @brief Result returned by moderation checks.
   */
  struct ModerationResult
  {
    bool ok{false};
    std::vector<std::string> errors{};
  };

  /**
   * @brief Lightweight moderation service for public wall inputs.
   *
   * This first version is intentionally simple:
   * - rejects blank text
   * - rejects texts containing blocked terms
   * - rejects excessively repeated characters
   */
  class ModerationService
  {
  public:
    /**
     * @brief Default constructor.
     */
    ModerationService();

    /**
     * @brief Construct with a custom blocked-word list.
     */
    explicit ModerationService(std::vector<std::string> blocked_terms);

    /**
     * @brief Moderate a posted message text.
     */
    ModerationResult moderate_message(std::string_view text) const;

    /**
     * @brief Check quickly whether a text is acceptable.
     */
    bool allow_message(std::string_view text) const;

    /**
     * @brief Access blocked terms.
     */
    const std::vector<std::string> &blocked_terms() const noexcept;

  private:
    std::vector<std::string> blocked_terms_{};

    bool contains_blocked_term(std::string_view text) const;
    static bool has_excessive_repetition(std::string_view text) noexcept;
  };

} // namespace wall::services

#endif // WALL_SERVICES_MODERATIONSERVICE_HPP
