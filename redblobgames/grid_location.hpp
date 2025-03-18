#pragma once

#include <iostream>
#include <tuple>

namespace redblobgames {

struct GridLocation {
  int x, y;
};

inline bool operator==(const GridLocation &lhs, const GridLocation &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(GridLocation const &a, GridLocation const &b) {
  return !(a == b);
}

inline bool operator<(GridLocation const &a, GridLocation const &b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

inline std::basic_iostream<char>::basic_ostream &
operator<<(std::basic_iostream<char>::basic_ostream &out,
           GridLocation const &loc) {
  out << '(' << loc.x << ',' << loc.y << ')';
  return out;
}
} // namespace redblobgames

namespace std {
template <> struct hash<redblobgames::GridLocation> {
  std::size_t operator()(redblobgames::GridLocation const &id) const noexcept {
    return std::hash<int>()(id.x ^ (id.y << 16));
  }
};
} // namespace std
