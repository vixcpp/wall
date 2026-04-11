/**
 * @file WallConfig.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/config/WallConfig.hpp>

#include <filesystem>
#include <utility>

#include <wall/util/Env.hpp>

namespace wall::config
{
  namespace
  {
    int clamp_at_least(int value, int minimum) noexcept
    {
      return value < minimum ? minimum : value;
    }

    std::string normalize_root(std::string root)
    {
      namespace fs = std::filesystem;

      if (root.empty())
      {
        return fs::current_path().lexically_normal().string();
      }

      fs::path p(root);

      if (p.is_relative())
      {
        p = fs::current_path() / p;
      }

      return p.lexically_normal().string();
    }

    std::string resolve_from_root(const std::string &root, std::string path)
    {
      namespace fs = std::filesystem;

      if (path.empty())
      {
        return path;
      }

      fs::path p(path);
      if (p.is_relative())
      {
        p = fs::path(root) / p;
      }

      return p.lexically_normal().string();
    }
  } // namespace

  WallConfig WallConfig::from_env()
  {
    return WallConfig(
        wall::util::Env::app_env(),
        wall::util::Env::app_root(),
        wall::util::Env::host(),
        clamp_at_least(wall::util::Env::port(), 1),
        clamp_at_least(wall::util::Env::ws_port(), 1),
        wall::util::Env::public_url(),
        wall::util::Env::database_path(),
        wall::util::Env::log_dir(),
        clamp_at_least(wall::util::Env::max_message_length(), 1),
        clamp_at_least(wall::util::Env::max_username_length(), 1),
        clamp_at_least(wall::util::Env::rate_limit_window_sec(), 1),
        clamp_at_least(wall::util::Env::rate_limit_max_requests(), 1),
        wall::util::Env::debug());
  }

  WallConfig::WallConfig(std::string app_env,
                         std::string app_root,
                         std::string host,
                         int port,
                         int ws_port,
                         std::string public_url,
                         std::string database_path,
                         std::string log_dir,
                         int max_message_length,
                         int max_username_length,
                         int rate_limit_window_sec,
                         int rate_limit_max_requests,
                         bool debug)
      : app_env_(std::move(app_env)),
        app_root_(normalize_root(std::move(app_root))),
        host_(std::move(host)),
        port_(clamp_at_least(port, 1)),
        ws_port_(clamp_at_least(ws_port, 1)),
        public_url_(std::move(public_url)),
        database_path_(resolve_from_root(app_root_, std::move(database_path))),
        log_dir_(resolve_from_root(app_root_, std::move(log_dir))),
        max_message_length_(clamp_at_least(max_message_length, 1)),
        max_username_length_(clamp_at_least(max_username_length, 1)),
        rate_limit_window_sec_(clamp_at_least(rate_limit_window_sec, 1)),
        rate_limit_max_requests_(clamp_at_least(rate_limit_max_requests, 1)),
        debug_(debug)
  {
  }

  const std::string &WallConfig::app_env() const noexcept
  {
    return app_env_;
  }

  const std::string &WallConfig::app_root() const noexcept
  {
    return app_root_;
  }

  const std::string &WallConfig::host() const noexcept
  {
    return host_;
  }

  int WallConfig::port() const noexcept
  {
    return port_;
  }

  int WallConfig::ws_port() const noexcept
  {
    return ws_port_;
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
