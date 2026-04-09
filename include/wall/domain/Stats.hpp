/**
 * @file Stats.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Domain model for public wall statistics.
 */

#ifndef WALL_DOMAIN_STATS_HPP
#define WALL_DOMAIN_STATS_HPP

#include <cstdint>

namespace wall::domain
{
  /**
   * @brief Aggregated public statistics for the wall.
   *
   * This model is intentionally small and focused on what the demo needs.
   */
  class Stats
  {
  public:
    /**
     * @brief Default constructor.
     */
    Stats() = default;

    /**
     * @brief Construct stats with all fields.
     */
    Stats(std::int64_t total_messages,
          std::int64_t total_reactions,
          std::int64_t online_sessions,
          std::int64_t generated_at_ms);

    /**
     * @brief Create an empty stats snapshot for "now".
     */
    static Stats create_empty();

    /**
     * @brief Get total number of messages.
     */
    std::int64_t total_messages() const noexcept;

    /**
     * @brief Get total number of reactions.
     */
    std::int64_t total_reactions() const noexcept;

    /**
     * @brief Get number of currently online sessions.
     */
    std::int64_t online_sessions() const noexcept;

    /**
     * @brief Get the generation timestamp in milliseconds since epoch.
     */
    std::int64_t generated_at_ms() const noexcept;

    /**
     * @brief Set total number of messages.
     */
    void set_total_messages(std::int64_t value) noexcept;

    /**
     * @brief Set total number of reactions.
     */
    void set_total_reactions(std::int64_t value) noexcept;

    /**
     * @brief Set number of online sessions.
     */
    void set_online_sessions(std::int64_t value) noexcept;

    /**
     * @brief Set the generation timestamp.
     */
    void set_generated_at_ms(std::int64_t value) noexcept;

    /**
     * @brief Increment total messages by one.
     */
    void increment_messages() noexcept;

    /**
     * @brief Increment total reactions by one.
     */
    void increment_reactions() noexcept;

  private:
    std::int64_t total_messages_{0};
    std::int64_t total_reactions_{0};
    std::int64_t online_sessions_{0};
    std::int64_t generated_at_ms_{0};
  };

} // namespace wall::domain

#endif // WALL_DOMAIN_STATS_HPP
