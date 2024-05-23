#include "ShortestPathAlgorithm.h"
#include "AStar.h"
#include "Utils.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct PriorityNode {
  double priority;
  long v;

  PriorityNode(double priority, long v) : priority(priority), v(v) { }
};

class PriorityNodeComparator
{
public:
    bool operator()(PriorityNode a, PriorityNode b) {
        return a.priority > b.priority;
    }
};

unordered_map<long, Edge> AStar::findShortestPath(
    Node& from, 
    Node& to, 
    unordered_map<long, vector<Edge>>& incidence_map
) {
    unordered_map<long, Edge> optimal_edges;
    unordered_map<long, double> costs;
    unordered_set<long> processed;

    priority_queue<PriorityNode, vector<PriorityNode>, PriorityNodeComparator> queue;
    queue.push(PriorityNode(0, from.id));

    while (!queue.empty()) {
        auto& current = queue.top();
        queue.pop();

        if (current.v == to.id) {
        break;
        }

        processed.insert(current.v);

        for (auto& edge: incidence_map[current.v]) {
        double new_cost = costs[current.v] + edge.dist;
        long other_v;
        double other_v_distance_to_end;
        if (edge.v == current.v) {
            other_v = edge.u;
            other_v_distance_to_end = eucledean_dist(edge.ux, edge.uy, to.x, to.y);
        } else {
            other_v = edge.v;
            other_v_distance_to_end = eucledean_dist(edge.vx, edge.vy, to.x, to.y);
        }
        if (processed.count(other_v) > 0) {
            continue;
        }
        if (costs.count(other_v) == 0 || new_cost < costs[other_v]) {
            costs[other_v] = new_cost;
            double priority = new_cost - other_v_distance_to_end; 
            queue.push(PriorityNode(priority, other_v));
            optimal_edges[other_v] = edge;
        }
        }
    }

    return optimal_edges;
}