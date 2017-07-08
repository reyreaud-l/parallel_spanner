#pragma once
#include <cmath>
#include "graph/graph.hh"
#include <iostream>
#include <unordered_set>
#include <queue>

void simple_greedy(Graph<>&, float);
double shortest_distance(Graph<>& graph,
                         Graph<>::vertex_descriptor src,
                         Graph<>::vertex_descriptor dest);
double pythagore(Graph<>& graph,
                 Graph<>::vertex_descriptor src,
                 Graph<>::vertex_descriptor dest);
std::map<Graph<>::vertex_descriptor, double>
dijkstra(Graph<>& graph, Graph<>::vertex_descriptor src,
         Graph<>::vertex_descriptor dest);
