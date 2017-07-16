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
  if (left && left->right != nullptr && left->left != nullptr)
  {
    res.push_back(left);
    auto son = left->get_all_nodes();
    res.insert(res.end(),
               std::make_move_iterator(son.begin()),
               std::make_move_iterator(son.end()));
  }
  if (right && right->left != nullptr && right->right != nullptr)
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
  root = calc_tree(points, rectangle);
}

std::shared_ptr<Node> SplitTree::calc_tree(std::vector<Point> points, Rectangle rectangle)
{
  Rectangle bounding_box(points);
  if (points.size() == 1)
    return std::make_shared<Node>(Node(bounding_box, points));
  bool i = bounding_box.get_dim_max_length();
  Line split_line = bounding_box.split_line_get(i);
  std::cout << "\n\n";
  std::cout << "Bounding box:\n" << bounding_box << std::endl;
  std::cout << "Split Line:\n" << split_line << std::endl;
  auto box_pair = rectangle.split(split_line);
  auto r1 = box_pair.first;
  auto r2 = box_pair.second;
  std::vector<Point> s1;
  std::vector<Point> s2;
  for (auto point : points)
  {
    if (r1.contains(point))
      s1.push_back(point);
    else if (r2.contains(point))
      s2.push_back(point);
  }

  std::cout << "Left:\n" << r1 << std::endl;
  std::cout << "Right:\n" << r2 << std::endl;
  auto left = calc_tree(s1, r1);
  auto right = calc_tree(s2, r2);
  return std::make_shared<Node>(Node(left, right, bounding_box, points));
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

std::vector<std::pair<std::vector<Point>, std::vector<Point>>>
wspd_decomposition(SplitTree tree, double s)
{
  std::vector<std::pair<std::vector<Point>, std::vector<Point>>> res;
  for (auto node : tree.get_all_nodes())
  {
    if (node->left == nullptr || node->right == nullptr)
      continue;
    auto tmp = find_pairs(*(node->left), *(node->right), s);
    res.insert(res.end(),
              std::make_move_iterator(tmp.begin()),
              std::make_move_iterator(tmp.end()));
  }
  return res;
}

bool is_well_separated(Node left, Node right, double s)
{
  auto radius_l = left.bounding_box.get_radius();
  auto radius_r = right.bounding_box.get_radius();
  auto center_l = left.bounding_box.get_center();
  auto center_r = right.bounding_box.get_center();

  double dist = center_l.distance(center_r) - (radius_l + radius_r);

  return dist >= s * std::max(radius_l, radius_r);
}

std::vector<std::pair<std::vector<Point>, std::vector<Point>>>
find_pairs(Node left, Node right, double s)
{
  using vec_pair = std::vector<std::pair<std::vector<Point>, std::vector<Point>>>;
  if (is_well_separated(left, right, s))
  {
    auto pair = std::pair<std::vector<Point>, std::vector<Point>>({left.points, right.points});
    return std::vector<decltype(pair)>({pair});
  }
  vec_pair pairs;
  if (left.bounding_box.get_max_length() <= right.bounding_box.get_max_length())
  {
    if (!right.left || !right.right)
      return pairs;
    auto right_l = right.left;
    auto right_r = right.right;

    auto r1 = find_pairs(left, *right_l, s);
    pairs.insert(pairs.end(),
                std::make_move_iterator(r1.begin()),
                std::make_move_iterator(r1.end()));

    r1 = find_pairs(left, *right_r, s);
    pairs.insert(pairs.end(),
                std::make_move_iterator(r1.begin()),
                std::make_move_iterator(r1.end()));
  }
  else
  {
    if (!left.left || !left.right)
      return pairs;
    auto left_l = left.left;
    auto left_r = left.right;

    auto r1 = find_pairs(*left_l, right, s);
    pairs.insert(pairs.end(),
                std::make_move_iterator(r1.begin()),
                std::make_move_iterator(r1.end()));

    r1 = find_pairs(*left_r, right, s);
    pairs.insert(pairs.end(),
                std::make_move_iterator(r1.begin()),
                std::make_move_iterator(r1.end()));
  }
  return pairs;
}
