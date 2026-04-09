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
