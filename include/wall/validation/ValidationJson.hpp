/**
 * @file ValidationJson.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#ifndef WALL_VALIDATION_VALIDATIONJSON_HPP
#define WALL_VALIDATION_VALIDATIONJSON_HPP

#include <vix/json/Simple.hpp>

#include <wall/validation/PostMessageInput.hpp>
#include <wall/validation/ReactInput.hpp>

namespace wall::validation
{
  /**
   * @brief JSON helpers for validation responses.
   */
  class ValidationJson
  {
  public:
    /**
     * @brief Convert a post-message validation result to JSON.
     */
    static vix::json::kvs to_json(const PostMessageValidationResult &result);

    /**
     * @brief Convert a reaction validation result to JSON.
     */
    static vix::json::kvs to_json(const ReactValidationResult &result);

    /**
     * @brief Build a generic validation error payload from a list of messages.
     */
    static vix::json::kvs error_payload(const std::vector<std::string> &errors);
  };

} // namespace wall::validation

#endif // WALL_VALIDATION_VALIDATIONJSON_HPP
