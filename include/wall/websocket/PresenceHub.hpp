/**
 * @file PresenceHub.hpp
 * @author Gaspard Kirira
 *
 * wall
 *
 * In-memory presence tracker for wall realtime sessions.
 */

#ifndef WALL_WEBSOCKET_PRESENCEHUB_HPP
#define WALL_WEBSOCKET_PRESENCEHUB_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

#include <wall/domain/Presence.hpp>

namespace wall::websocket
{
  /**
   * @brief Thread-safe in-memory presence tracker.
   *
   * PresenceHub stores active wall sessions and exposes simple helpers
   * for connect, disconnect, touch and count operations.
   */
  class PresenceHub
  {
  public:
    /**
     * @brief Register a new online session.
     *
     * @return The created presence object.
     */
    wall::domain::Presence connect();

    /**
     * @brief Remove a session from the hub.
     *
     * @return true if the session existed and was removed.
     */
    bool disconnect(const std::string &session_id);

    /**
     * @brief Mark a session as active now.
     *
     * @return true if the session exists.
     */
    bool touch(const std::string &session_id);

    /**
     * @brief Check whether a session exists.
     */
    bool exists(const std::string &session_id) const;

    /**
     * @brief Return the number of online sessions.
     */
    std::int64_t online_count() const noexcept;

    /**
     * @brief Return a snapshot of all active presences.
     */
    std::vector<wall::domain::Presence> snapshot() const;

    /**
     * @brief Remove all sessions.
     */
    void clear();

  private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, wall::domain::Presence> sessions_;
  };

} // namespace wall::websocket

#endif // WALL_WEBSOCKET_PRESENCEHUB_HPP
