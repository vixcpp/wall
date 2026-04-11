/**
 * @file StatsJson.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
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
