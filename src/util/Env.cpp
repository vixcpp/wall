#include <wall/util/Env.hpp>

#include <vix/utils/Env.hpp>

namespace wall::util
{
  std::string Env::app_env()
  {
    return vix::utils::env_or("WALL_APP_ENV", "development");
  }

  bool Env::is_production()
  {
    return app_env() == "production";
  }

  bool Env::is_development()
  {
    return app_env() == "development";
  }

  std::string Env::host()
  {
    return vix::utils::env_or("WALL_HOST", "0.0.0.0");
  }

  int Env::port()
  {
    return vix::utils::env_int("WALL_PORT", 8080);
  }

  std::string Env::public_url()
  {
    return vix::utils::env_or("WALL_PUBLIC_URL", "http://localhost:8080");
  }

  std::string Env::database_path()
  {
    return vix::utils::env_or("WALL_DB_PATH", "data/wall.db");
  }

  std::string Env::log_dir()
  {
    return vix::utils::env_or("WALL_LOG_DIR", "data/logs");
  }

  int Env::max_message_length()
  {
    return vix::utils::env_int("WALL_MAX_MESSAGE_LENGTH", 160);
  }

  int Env::max_username_length()
  {
    return vix::utils::env_int("WALL_MAX_USERNAME_LENGTH", 20);
  }

  int Env::rate_limit_window_sec()
  {
    return vix::utils::env_int("WALL_RATE_LIMIT_WINDOW_SEC", 30);
  }

  int Env::rate_limit_max_requests()
  {
    return vix::utils::env_int("WALL_RATE_LIMIT_MAX_REQUESTS", 10);
  }

  bool Env::debug()
  {
    return vix::utils::env_bool("WALL_DEBUG", false);
  }

} // namespace wall::util
