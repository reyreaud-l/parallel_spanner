#pragma once

#include <vector>
#include <cmath>
#include <climits>


class Point
{
  public:
  Point() {}
  Point(double x, double y)
  : x(x)
  , y(y)
  {}

  bool operator==(const Point& r)
  {
    return x == r.x && y == r.y;
  }

  double distance(Point v)
  {
    return std::sqrt(std::pow(v.x - x, 2) + std::pow(v.y - y, 2));
  }
  double x;
  double y;
};

class Line
{
  public:
  // dir == true => line is horizontal
  Line(Point s, Point d, bool dir)
  : src(s)
  , dst(d)
  , horizontal(dir)
  {}

  Point src;
  Point dst;
  bool horizontal;
};

class Rectangle
{
  public:
  Rectangle() {};
  Rectangle(Point a, Point b, Point c, Point d)
  : top_left(a)
  , bottom_left(b)
  , top_right(c)
  , bottom_right(d)
  {}

  Rectangle(std::vector<Point>);
  bool contains(Point);
  bool get_dim_max_length();
  Line split_line_get(bool);
  std::pair<Rectangle, Rectangle> split(Line);
  double get_max_length();

  Point get_center()
  {
    return Point((bottom_left.x + top_right.x) / 2, (bottom_left.y + top_left.y) / 2);
  }

  double get_radius()
  {
    return bottom_left.distance(top_right);
  }

  Point top_left;
  Point bottom_left;
  Point top_right;
  Point bottom_right;
};
