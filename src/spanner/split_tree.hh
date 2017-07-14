#pragma once

#include <vector>
#include <memory>
#include <iterator>
#include <iostream>
#include "rectangle.hh"

class Node
{
  public:
  Node() {};
  Node(Rectangle, std::vector<Point>);
  Node(std::shared_ptr<Node>, std::shared_ptr<Node>, Rectangle,
      std::vector<Point>);

  std::vector<std::shared_ptr<Node>> get_all_nodes();

  std::vector<Point> points;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;
  Rectangle bounding_box;
};

class SplitTree
{
  public:
  SplitTree(std::vector<Point>, Rectangle);
  std::shared_ptr<Node> calc_tree(std::vector<Point>, Rectangle);

  std::vector<std::shared_ptr<Node>> get_all_nodes();
  std::shared_ptr<Node> root;
};

std::vector<std::pair<std::vector<Point>, std::vector<Point>>>
wspd_decomposition(SplitTree tree, double s);

std::vector<std::pair<std::vector<Point>, std::vector<Point>>>
find_pairs(Node left, Node right, double s);
