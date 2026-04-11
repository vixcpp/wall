/**
 * @file App.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/app/App.hpp>

#include <utility>

namespace wall::app
{
  App::App(wall::config::WallConfig config)
      : bootstrap_(std::move(config))
  {
  }

  App App::from_env()
  {
    return App(wall::config::WallConfig::from_env());
  }

  wall::app::Bootstrap &App::bootstrap() noexcept
  {
    return bootstrap_;
  }

  const wall::app::Bootstrap &App::bootstrap() const noexcept
  {
    return bootstrap_;
  }

  void App::run()
  {
    bootstrap_.run();
  }

} // namespace wall::app
