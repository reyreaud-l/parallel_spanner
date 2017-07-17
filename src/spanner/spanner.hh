#pragma once

#include "global.hh"
#include "graph/graph.hh"
#include "tbb/concurrent_priority_queue.h"
#include <cmath>
#include <iostream>
#include <queue>
#include <tbb/atomic.h>
#include <tbb/task_group.h>
#include <tbb/spin_mutex.h>
#include <unordered_set>


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

void parallel_greedy(Graph<>& graph, float t);
