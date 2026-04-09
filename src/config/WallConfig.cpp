#include <wall/config/WallConfig.hpp>

#include <utility>

#include <wall/util/Env.hpp>

namespace wall::config
{
  WallConfig WallConfig::from_env()
  {
    return WallConfig(
        wall::util::Env::app_env(),
        wall::util::Env::host(),
        wall::util::Env::port(),
        wall::util::Env::public_url(),
        wall::util::Env::database_path(),
        wall::util::Env::log_dir(),
        wall::util::Env::max_message_length(),
        wall::util::Env::max_username_length(),
        wall::util::Env::rate_limit_window_sec(),
        wall::util::Env::rate_limit_max_requests(),
        wall::util::Env::debug());
  }

  WallConfig::WallConfig(std::string app_env,
                         std::string host,
                         int port,
                         std::string public_url,
                         std::string database_path,
                         std::string log_dir,
                         int max_message_length,
                         int max_username_length,
                         int rate_limit_window_sec,
                         int rate_limit_max_requests,
                         bool debug)
      : app_env_(std::move(app_env)),
        host_(std::move(host)),
        port_(port),
        public_url_(std::move(public_url)),
        database_path_(std::move(database_path)),
        log_dir_(std::move(log_dir)),
        max_message_length_(max_message_length),
        max_username_length_(max_username_length),
        rate_limit_window_sec_(rate_limit_window_sec),
        rate_limit_max_requests_(rate_limit_max_requests),
        debug_(debug)
  {
  }

  const std::string &WallConfig::app_env() const noexcept
  {
    return app_env_;
  }

  const std::string &WallConfig::host() const noexcept
  {
    return host_;
  }

  int WallConfig::port() const noexcept
  {
    return port_;
  }

  const std::string &WallConfig::public_url() const noexcept
  {
    return public_url_;
  }

  const std::string &WallConfig::database_path() const noexcept
  {
    return database_path_;
  }

  const std::string &WallConfig::log_dir() const noexcept
  {
    return log_dir_;
  }

  int WallConfig::max_message_length() const noexcept
  {
    return max_message_length_;
  }

  int WallConfig::max_username_length() const noexcept
  {
    return max_username_length_;
  }

  int WallConfig::rate_limit_window_sec() const noexcept
  {
    return rate_limit_window_sec_;
  }

  int WallConfig::rate_limit_max_requests() const noexcept
  {
    return rate_limit_max_requests_;
  }

  bool WallConfig::debug() const noexcept
  {
    return debug_;
  }

  bool WallConfig::is_production() const noexcept
  {
    return app_env_ == "production";
  }

  bool WallConfig::is_development() const noexcept
  {
    return app_env_ == "development";
  }

} // namespace wall::config
