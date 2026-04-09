/**
 * @file StatsService.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Application service for wall statistics.
 */

#ifndef WALL_SERVICES_STATSSERVICE_HPP
#define WALL_SERVICES_STATSSERVICE_HPP

#include <cstdint>

#include <wall/domain/Stats.hpp>
#include <wall/storage/StatsRepository.hpp>

namespace wall::services
{
  /**
   * @brief Application service responsible for wall statistics.
   */
  class StatsService
  {
  public:
    /**
     * @brief Construct a stats service.
     */
    explicit StatsService(wall::storage::StatsRepository &repository);

    /**
     * @brief Build a stats snapshot.
     *
     * @param online_sessions Current online sessions count from the
     *        in-memory presence tracker.
     */
    wall::domain::Stats snapshot(std::int64_t online_sessions);

    /**
     * @brief Count total persisted messages.
     */
    std::int64_t count_messages();

    /**
     * @brief Count total persisted reactions.
     */
    std::int64_t count_reactions();

  private:
    wall::storage::StatsRepository &repository_;
  };

} // namespace wall::services

#endif // WALL_SERVICES_STATSSERVICE_HPP
