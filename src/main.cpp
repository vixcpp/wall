/**
 * @file main.cpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * Entry point for the wall backend.
 */

#include <exception>
#include <iostream>

#include <wall/app/App.hpp>

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
    std::cerr << "[wall] fatal error: " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "[wall] fatal error: unknown exception\n";
    return 1;
  }
}
