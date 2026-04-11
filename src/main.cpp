/**
 * @file main.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <exception>
#include <wall/app/App.hpp>
#include <vix/console.hpp>

int main()
{
  try
  {
    auto app = wall::app::App::from_env();
    app.run();
    return 0;
  }
  catch (const std::exception &e)
  {
    vix::console.error("[wall] fatal error: ", e.what());
    return 1;
  }
  catch (...)
  {
    vix::console.error("[wall] fatal error: unknown exception");
    return 1;
  }
}
