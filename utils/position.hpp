#ifndef POSITION_HPP
#define POSITION_HPP

template <typename T>
struct Position
{
  Position() {}

  Position(T x, T y)
    : x{x}
    , y{y}
  {}

  Position& operator-(const Position& position)
  {
    x -= position.x;
    y -= position.y;
    return *this;
  }

  Position& operator+(const Position& position)
  {
    x += position.x;
    y += position.y;
    return *this;
  }

  Position& operator*(const Position& position)
  {
    x *= position.x;
    y *= position.y;
    return *this;
  }

  Position& operator/(const Position& position)
  {
    x /= position.x;
    y /= position.y;
    return *this;
  }

  bool operator==(const Position& position) const
  {
    return ( x == position.x &&
             y == position.y );
  }

  T x {0};
  T y {0};
};

#endif // POSITION_HPP

