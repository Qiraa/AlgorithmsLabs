#pragma once

#include "ShortestPathAlgorithm.h"
#include "Node.h"
#include "Edge.h"

class Dijkstra: public ShortestPathAlgorithm {
    public:
    unordered_map<long, Edge> findShortestPath(
        Node& from, 
        Node& to, 
        unordered_map<long, vector<Edge>>& incidence_map
    ) override;
};