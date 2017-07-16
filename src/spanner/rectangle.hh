#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <climits>


class Point
{
  public:
  Point() {}
  Point(double x, double y, int vertice = 0, std::string name = "ABORT_MISSION")
  : x(x)
  , y(y)
  , vertice(vertice)
  , name(name)
  {}

  bool operator==(const Point& r)
  {
    return x == r.x && y == r.y;
  }

  double distance(Point v)
  {
    return std::sqrt(std::pow(v.x - x, 2) + std::pow(v.y - y, 2));
  }

  friend std::ostream& operator<<(std::ostream& ostr_, Point& v)
  {
    ostr_ << "x: " << v.x << " y: " << v.y;
    return ostr_;
  }
  double x;
  double y;
  int vertice;
  std::string name;
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

  friend std::ostream& operator<<(std::ostream& ostr_, Line& v)
  {
    ostr_ << "\tSrc " << v.src << "\n\tDst " << v.dst;
    return ostr_;
  }

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
    return bottom_left.distance(top_right) / 2;
  }

  friend std::ostream& operator<<(std::ostream& ostr_, Rectangle& v)
  {
    ostr_ << "\ttop_left: " << v.top_left << std::endl;
    ostr_ << "\ttop_right: " << v.top_right << std::endl;
    ostr_ << "\tbottom_left: " << v.bottom_left << std::endl;
    ostr_ << "\tbottom_right: " << v.bottom_right;
    return ostr_;
  }

  Point top_left;
  Point bottom_left;
  Point top_right;
  Point bottom_right;
};
