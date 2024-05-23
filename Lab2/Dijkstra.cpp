#include "ShortestPathAlgorithm.h"
#include "Dijkstra.h"
#include <vector>
#include <unordered_map>
#include <limits>
#include <unordered_set>

unordered_map<long, Edge> Dijkstra::findShortestPath(
  Node& from, 
  Node& to,
  unordered_map<long, vector<Edge>>& incidence_map
) {
  unordered_map<long, Edge> optimal_edges;
  unordered_map<long, double> distances;
  unordered_set<long> processed;
  for (auto pair: incidence_map) {
    distances[pair.first] = numeric_limits<double>::infinity();
  }
  distances[from.id] = 0.0;

  while (true) {
    long closest_v = -1; 
    double min_distance = numeric_limits<double>::infinity();
    for (auto pair: incidence_map) {
      long v = pair.first;
      if (processed.count(v) == 0 && distances[v] < min_distance) {
        closest_v = v;
        min_distance = distances[v];
      }
    }

    if (closest_v == -1 || closest_v == to.id) {
      break;
    }

    for (auto edge: incidence_map[closest_v]) {
      long other_v;
      if (edge.u == closest_v) {
        other_v = edge.v;
      } else {
        other_v = edge.u;
      }
      double current_distance = min_distance + edge.dist;
      double old_distance = distances[other_v];
      if (current_distance < old_distance) {
        optimal_edges[other_v] = edge;
        distances[other_v] = current_distance;
      }
    }

    processed.insert(closest_v);
  }

  return optimal_edges;
}