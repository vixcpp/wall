/**
 * @file StatsJson.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/json/StatsJson.hpp>

namespace wall::json
{
  vix::json::kvs StatsJson::to_json(const wall::domain::Stats &stats)
  {
    return vix::json::obj({
        "total_messages",
        stats.total_messages(),
        "total_reactions",
        stats.total_reactions(),
        "online_sessions",
        stats.online_sessions(),
        "generated_at_ms",
        stats.generated_at_ms(),
    });
  }

} // namespace wall::json
