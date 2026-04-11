/**
 * @file WallService.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/services/WallService.hpp>

namespace wall::services
{
  WallService::WallService(MessageService &message_service,
                           ReactionService &reaction_service,
                           StatsService &stats_service,
                           ModerationService &moderation_service)
      : message_service_(message_service),
        reaction_service_(reaction_service),
        stats_service_(stats_service),
        moderation_service_(moderation_service)
  {
  }

  WallPostResult WallService::post_message(const wall::validation::PostMessageInput &input)
  {
    const auto moderation = moderation_service_.moderate_message(input.text());

    if (!moderation.ok)
    {
      return WallPostResult{
          .ok = false,
          .message = std::nullopt,
          .errors = moderation.errors};
    }

    const auto result = message_service_.post(input);

    return WallPostResult{
        .ok = result.ok,
        .message = result.message,
        .errors = result.errors};
  }

  ReactResult WallService::react(const wall::validation::ReactInput &input)
  {
    return reaction_service_.react(input);
  }

  std::vector<wall::domain::Message> WallService::latest_messages(std::size_t limit)
  {
    return message_service_.latest(limit);
  }

  wall::domain::Stats WallService::stats(std::int64_t online_sessions)
  {
    return stats_service_.snapshot(online_sessions);
  }

  std::optional<wall::domain::Message>
  WallService::find_message_by_id(const std::string &id)
  {
    return message_service_.find_by_id(id);
  }

} // namespace wall::services
