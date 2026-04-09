/**
 * @file MessageJson.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * JSON serialization helpers for wall messages.
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
