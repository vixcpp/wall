#include <wall/websocket/WallEvents.hpp>

namespace wall::websocket
{
  bool WallEvents::is_wall_event(std::string_view name) noexcept
  {
    return name == message ||
           name == reaction ||
           name == presence ||
           name == stats ||
           name == error ||
           name == hello;
  }

} // namespace wall::websocket
