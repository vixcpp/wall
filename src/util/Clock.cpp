#include <wall/util/Clock.hpp>

namespace wall::util
{
  using vix::time::Duration;
  using vix::time::Timestamp;

  Timestamp Clock::now() noexcept
  {
    return Timestamp::now();
  }

  std::int64_t Clock::now_ms() noexcept
  {
    return Timestamp::now().nanoseconds_since_epoch() / 1'000'000LL;
  }

  std::int64_t Clock::now_sec() noexcept
  {
    return Timestamp::now().seconds_since_epoch();
  }

  Duration Clock::since(const Timestamp &t0) noexcept
  {
    return Timestamp::now() - t0;
  }

  std::int64_t Clock::since_ms(const Timestamp &t0) noexcept
  {
    return (Timestamp::now() - t0).count_ms();
  }

} // namespace wall::util
