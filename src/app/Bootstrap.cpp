#include <wall/app/Bootstrap.hpp>

#include <stdexcept>
#include <utility>

namespace wall::app
{
  Bootstrap::Bootstrap(wall::config::WallConfig config)
      : context_(std::move(config))
  {
  }

  wall::app::ServerContext &Bootstrap::context() noexcept
  {
    return context_;
  }

  const wall::app::ServerContext &Bootstrap::context() const noexcept
  {
    return context_;
  }

  void Bootstrap::install()
  {
    if (installed_)
      return;

    context_.wall_websocket().install();
    context_.http_server().install_routes();

    installed_ = true;
  }

  void Bootstrap::run()
  {
    if (!installed_)
    {
      install();
    }

    context_.http_server().run();
  }

} // namespace wall::app
