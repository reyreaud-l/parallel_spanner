#include "spanner/split_tree.hh"


Node::Node(Rectangle rec, std::vector<Point> ps)
{
  left = nullptr;
  right = nullptr;
  points = ps;
  bounding_box = rec;
}

Node::Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r, Rectangle rec,
      std::vector<Point> ps)
{
  left = l;
  right = r;
  points = ps;
  bounding_box = rec;
}

std::vector<std::shared_ptr<Node>> Node::get_all_nodes()
{
  std::vector<std::shared_ptr<Node>> res;
  if (left)
  {
    res.push_back(left);
    auto son = left->get_all_nodes();
    res.insert(res.end(),
               std::make_move_iterator(son.begin()),
               std::make_move_iterator(son.end()));
  }
  if (right)
  {
    res.push_back(right);
    auto son = right->get_all_nodes();
    res.insert(res.end(),
               std::make_move_iterator(son.begin()),
               std::make_move_iterator(son.end()));
  }
  return res;
}

SplitTree::SplitTree(std::vector<Point> points, Rectangle rectangle)
{
  root = std::make_shared<Node>(calc_tree(points, rectangle));
}

Node SplitTree::calc_tree(std::vector<Point> points, Rectangle rectangle)
{
  Rectangle bounding_box(points);
  if (points.size() == 1)
    return Node(bounding_box, points); 
  bool i = bounding_box.get_dim_max_length();
  Line split_line = bounding_box.split_line_get(i);
  auto box_pair = rectangle.split(split_line);
  auto r1 = box_pair.first;
  auto r2 = box_pair.second;
  std::vector<Point> s1;
  std::vector<Point> s2;
  for (auto point : points)
  {
    if (r1.contains(point))
      s1.push_back(point);
    else
      s2.push_back(point);
  }

  auto left = calc_tree(s1, r1);
  auto right = calc_tree(s2, r2);
  return Node(std::make_shared<Node>(left),
              std::make_shared<Node>(right),
              bounding_box,
              points);
}

std::vector<std::shared_ptr<Node>> SplitTree::get_all_nodes()
{
  std::vector<std::shared_ptr<Node>> res;
  res.push_back(root);
  auto son = root->get_all_nodes();
  res.insert(res.end(),
             std::make_move_iterator(son.begin()),
             std::make_move_iterator(son.end()));
  return res;
}
