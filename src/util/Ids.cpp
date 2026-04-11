/**
 * @file Ids.cpp
 * @author Gaspard Kirira
 *
 * Copyright 2026, Gaspard Kirira. All rights reserved.
 *
 * wall
 * Live production application built with Vix.cpp.
 *
 * Use of this source code is governed by the project license.
 */
#include <wall/util/Ids.hpp>

#include <array>
#include <cstdint>
#include <random>
#include <sstream>
#include <string>

#include <wall/util/Clock.hpp>

namespace wall::util
{
  namespace
  {
    std::mt19937_64 &rng()
    {
      static std::mt19937_64 engine{std::random_device{}()};
      return engine;
    }
  } // namespace

  std::string Ids::make(std::string_view prefix)
  {
    std::ostringstream oss;
    oss << prefix
        << '_'
        << Clock::now_ms()
        << '_'
        << random_hex(8);

    return oss.str();
  }

  std::string Ids::message()
  {
    return make("msg");
  }

  std::string Ids::reaction()
  {
    return make("react");
  }

  std::string Ids::event()
  {
    return make("evt");
  }

  std::string Ids::session()
  {
    return make("sess");
  }

  std::string Ids::random_hex(unsigned int hex_len)
  {
    static constexpr std::array<char, 16> hex = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f'};

    std::uniform_int_distribution<int> dist(0, 15);

    std::string out;
    out.reserve(hex_len);

    for (unsigned int i = 0; i < hex_len; ++i)
    {
      out.push_back(hex[static_cast<std::size_t>(dist(rng()))]);
    }

    return out;
  }

} // namespace wall::util
