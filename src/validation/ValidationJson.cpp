#include <wall/validation/ValidationJson.hpp>

namespace wall::validation
{
  namespace
  {
    vix::json::array_t errors_array(const std::vector<std::string> &errors)
    {
      vix::json::array_t items;
      items.reserve(errors.size());

      for (const auto &error : errors)
      {
        items.push_back(error);
      }

      return items;
    }
  } // namespace

  vix::json::kvs ValidationJson::to_json(const PostMessageValidationResult &result)
  {
    return vix::json::obj({
        "ok",
        result.ok,
        "error",
        result.ok ? "" : "validation_failed",
        "errors",
        errors_array(result.errors),
    });
  }

  vix::json::kvs ValidationJson::to_json(const ReactValidationResult &result)
  {
    return vix::json::obj({
        "ok",
        result.ok,
        "error",
        result.ok ? "" : "validation_failed",
        "errors",
        errors_array(result.errors),
    });
  }

  vix::json::kvs ValidationJson::error_payload(const std::vector<std::string> &errors)
  {
    const bool ok = errors.empty();

    return vix::json::obj({
        "ok",
        ok,
        "error",
        ok ? "" : "validation_failed",
        "errors",
        errors_array(errors),
    });
  }

} // namespace wall::validation
