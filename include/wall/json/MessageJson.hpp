/**
 * @file MessageJson.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */

#ifndef WALL_JSON_MESSAGEJSON_HPP
#define WALL_JSON_MESSAGEJSON_HPP

#include <vector>

#include <vix/json/Simple.hpp>
#include <wall/domain/Message.hpp>

namespace wall::json
{
  /**
   * @brief JSON helpers for wall messages.
   */
  class MessageJson
  {
  public:
    /**
     * @brief Convert a message to a JSON object.
     */
    static vix::json::kvs to_json(const wall::domain::Message &message);

    /**
     * @brief Convert a list of messages to a JSON array.
     */
    static vix::json::array_t to_array(
        const std::vector<wall::domain::Message> &messages);
  };

} // namespace wall::json

#endif // WALL_JSON_MESSAGEJSON_HPP
