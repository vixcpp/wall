/**
 * @file WallService.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Central application service for wall operations.
 */

#ifndef WALL_SERVICES_WALLSERVICE_HPP
#define WALL_SERVICES_WALLSERVICE_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <wall/domain/Message.hpp>
#include <wall/domain/Stats.hpp>
#include <wall/services/MessageService.hpp>
#include <wall/services/ModerationService.hpp>
#include <wall/services/ReactionService.hpp>
#include <wall/services/StatsService.hpp>
#include <wall/validation/PostMessageInput.hpp>
#include <wall/validation/ReactInput.hpp>

namespace wall::services
{
  /**
   * @brief Result returned when posting a moderated message.
   */
  struct WallPostResult
  {
    bool ok{false};
    std::optional<wall::domain::Message> message{};
    std::vector<std::string> errors{};
  };

  /**
   * @brief Central orchestration service for wall operations.
   */
  class WallService
  {
  public:
    /**
     * @brief Construct the wall service.
     */
    WallService(MessageService &message_service,
                ReactionService &reaction_service,
                StatsService &stats_service,
                ModerationService &moderation_service);

    /**
     * @brief Post a new wall message with moderation.
     */
    WallPostResult post_message(const wall::validation::PostMessageInput &input);

    /**
     * @brief Create a reaction on a wall message.
     */
    ReactResult react(const wall::validation::ReactInput &input);

    /**
     * @brief Return the latest wall messages.
     */
    std::vector<wall::domain::Message> latest_messages(std::size_t limit);

    /**
     * @brief Return a stats snapshot.
     */
    wall::domain::Stats stats(std::int64_t online_sessions);

    /**
     * @brief Find a message by id.
     */
    std::optional<wall::domain::Message> find_message_by_id(const std::string &id);

  private:
    MessageService &message_service_;
    ReactionService &reaction_service_;
    StatsService &stats_service_;
    ModerationService &moderation_service_;
  };

} // namespace wall::services

#endif // WALL_SERVICES_WALLSERVICE_HPP
