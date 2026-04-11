/**
 * @file StatsService.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/services/StatsService.hpp>

namespace wall::services
{
  StatsService::StatsService(wall::storage::StatsRepository &repository)
      : repository_(repository)
  {
  }

  wall::domain::Stats StatsService::snapshot(std::int64_t online_sessions)
  {
    return repository_.snapshot(online_sessions);
  }

  std::int64_t StatsService::count_messages()
  {
    return repository_.count_messages();
  }

  std::int64_t StatsService::count_reactions()
  {
    return repository_.count_reactions();
  }

} // namespace wall::services
