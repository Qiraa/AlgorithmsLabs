// Команда для компиляции: clang++ -std=c++20 -pedantic -pedantic-errors -Wall  -Wextra $(pkg-config --libs --cflags raylib) main.cpp -o main

#include "raylib.h"
#include "Node.h"
#include "Edge.h"
#include "Utils.h"
#include "ShortestPathAlgorithm.h"
#include "Dijkstra.h"
#include "AStar.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

const int CANVAS_WIDTH = 1200;
const int CANVAS_HEIGHT = 1000;

using namespace std;

vector<Node> read_nodes(string path) {
  fstream csv(path);

  string header;
  getline(csv, header);

  vector<Node> nodes;
  for (string line; getline(csv, line);) {
    stringstream lineStream(line);
    string cell;

    getline(lineStream, cell, ',');
    long id = stol(cell);

    getline(lineStream, cell, ',');
    double lon = stod(cell);

    getline(lineStream, cell, ',');
    double lat = stod(cell);

    nodes.emplace_back(id, lon, lat);
  }

  return nodes;
}

vector<Edge> read_edges(string path) {
  fstream csv(path);

  string header;
  getline(csv, header);

  vector<Edge> edges;
  for (string line; getline(csv, line);) {
    stringstream lineStream(line);
    string cell;

    getline(lineStream, cell, ',');
    long u = stol(cell);

    getline(lineStream, cell, ',');
    long v = stol(cell);

    edges.emplace_back(u, v);
  }

  return edges;
}

unordered_map<long, vector<Edge>> incidence_map(vector<Edge> edges) {
  unordered_map<long, vector<Edge>> result;
  for (Edge edge: edges) {
    result[edge.u].push_back(edge);
    result[edge.v].push_back(edge);
  }
  return result;
}

inline bool operator == (const Edge& lhs, const Edge& rhs) {
  return (lhs.u == rhs.u) && (lhs.v == rhs.v) || 
          (lhs.u == rhs.v) && (lhs.v == rhs.u); 
}

struct EdgeHash {
  size_t operator()(const Edge &edge) const {
      return std::max(edge.u, edge.v) * 13 + std::min(edge.u, edge.v);
  }
};

int main() {
  auto nodes = read_nodes("omsk/nodes.csv");
  auto edges = read_edges("omsk/edges.csv");

  unordered_map<long, size_t> node_id_to_pos;
  for (size_t i = 0; i < nodes.size(); i++) {
    auto& node = nodes[i];
    node_id_to_pos[node.id] = i;
  }

  double min_lon = nodes[0].lon;
  double max_lon = nodes[0].lon;
  double min_lat = nodes[0].lat;
  double max_lat = nodes[0].lat;

  for (auto &node : nodes) {
    if (min_lat > node.lat) {
      min_lat = node.lat;
    }
    if (min_lon > node.lon) {
      min_lon = node.lon;
    }
    if (max_lat < node.lat) {
      max_lat = node.lat;
    }
    if (max_lon < node.lon) {
      max_lon = node.lon;
    }
  }

  double delta_lon = max_lon - min_lon;
  double delta_lat = max_lat - min_lat;
  double scale = double(CANVAS_HEIGHT) / min(delta_lat, delta_lon);

  for (auto& node: nodes) {
    node.x = (node.lon - min_lon) * scale;
    node.y = CANVAS_HEIGHT - ( node.lat - min_lat) * scale;
  }

  for (auto& edge: edges) {
    auto& u = nodes[node_id_to_pos[edge.u]];
    auto& v = nodes[node_id_to_pos[edge.v]]; 
    edge.ux = u.x;
    edge.uy = u.y;
    edge.vx = v.x;
    edge.vy = v.y;

    edge.dist = eucledean_dist(edge.ux, edge.uy, edge.vx, edge.vy);
  }

  long from_id;
  long to_id;
  cout << "Enter from id: ";
  cin >> from_id;
  cout << "Enter to id: ";
  cin >> to_id;
  Node from = nodes[node_id_to_pos[from_id]];
  Node to = nodes[node_id_to_pos[to_id]];
  auto incmap = incidence_map(edges);

  cout << "Select algorithm" << endl;
  cout << "1. Dijkstra" << endl;
  cout << "2. A*" << endl;

  int option;
  cin >> option;

  ShortestPathAlgorithm* algorithm;
  switch (option)
  {
  case 1:
    algorithm = new Dijkstra();
    break;
  case 2:
    algorithm = new AStar();
    break;
  default:
    cout << "Invalid algorithm" << endl;
    exit(1);
    break;
  }

  auto optimal_edges = algorithm->findShortestPath(from, to, incmap);
  unordered_set<Edge, EdgeHash> used_edges;

  long current_v = to.id;
  while (current_v != from.id) {
    Edge& edge = optimal_edges[current_v];
    long other_v;
    if (edge.u == current_v) {
      other_v = edge.v;
    } else {
      other_v = edge.u;
    }
    used_edges.insert(edge);
    current_v = other_v;
  }

  InitWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "OMSK");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      for (auto& node: nodes) {
        DrawCircle(node.x, node.y, 1.5, RED);
      }
      for (auto& edge: edges) {
        if (used_edges.count(edge) > 0) {
          DrawLine(edge.ux, edge.uy, edge.vx, edge.vy, RED);
        } else {
          DrawLine(edge.ux, edge.uy, edge.vx, edge.vy, BLACK);
        }
      }
    EndDrawing();
  }
  CloseWindow();

  delete algorithm;
  return 0;
}