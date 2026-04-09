/**
 * @file StatsJson.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * JSON serialization helpers for wall statistics.
 */

#ifndef WALL_JSON_STATSJSON_HPP
#define WALL_JSON_STATSJSON_HPP

#include <vix/json/Simple.hpp>

#include <wall/domain/Stats.hpp>

namespace wall::json
{
  /**
   * @brief JSON helpers for wall statistics.
   */
  class StatsJson
  {
  public:
    /**
     * @brief Convert stats to a JSON object.
     */
    static vix::json::kvs to_json(const wall::domain::Stats &stats);
  };

} // namespace wall::json

#endif // WALL_JSON_STATSJSON_HPP
