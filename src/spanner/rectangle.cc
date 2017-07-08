#include "rectangle.hh"

Rectangle::Rectangle(std::vector<Point> points)
{
  double left_bound = INT_MIN;
  double right_bound = INT_MAX;
  double bottom_bound = INT_MIN;
  double top_bound = INT_MAX;

  for (Point point : points)
  {
    left_bound = std::min(point.x, left_bound);
    bottom_bound = std::min(point.y, bottom_bound);
    right_bound = std::max(point.x, right_bound);
    top_bound = std::max(point.x, top_bound);
  }

  top_left = Point(left_bound, top_bound);
  top_right = Point(right_bound, top_bound);
  bottom_left = Point(left_bound, bottom_bound);
  bottom_right = Point(right_bound, bottom_bound);
}

bool Rectangle::contains(Point point)
{
  return top_left.x <= point.x && point.x <= top_right.x
    && bottom_left.y <= point.y && point.y <= bottom_right.y;
}

bool Rectangle::get_dim_max_length()
{
  return !((top_right.x - top_left.x) > (top_left.y - bottom_left.y));
}

Line Rectangle::split_line_get(bool horizontal)
{
  if (horizontal)
    return Line(Point(top_left.x, (top_left.y + bottom_left.y) / 2),
                Point(top_right.x, (top_left.y + bottom_left.y) / 2),
                horizontal);
  return Line(Point((top_left.x + top_right.x / 2), top_left.y),
              Point((bottom_left.x + bottom_right.x) / 2, bottom_left.y),
              horizontal);
}

std::pair<Rectangle, Rectangle> Rectangle::split(Line split_line)
{
  if (split_line.horizontal)
  {
    Rectangle top(top_left,
                  Point(bottom_left.x, split_line.dst.y),
                  top_right,
                  Point(bottom_right.x, split_line.dst.y));
    Rectangle bottom(Point(top_left.x, split_line.dst.y),
                  bottom_left,
                  Point(top_right.x, split_line.dst.y),
                  bottom_right);
    return std::make_pair<>(top, bottom);
  }
  Rectangle left(top_left,
                bottom_left,
                Point(split_line.dst.x, top_right.y),
                Point(split_line.dst.x, bottom_right.y));
  Rectangle right(Point(split_line.dst.x, top_left.y),
                Point(split_line.dst.x, bottom_left.y),
                top_right,
                bottom_right);
  return std::make_pair<>(left, right);
}
