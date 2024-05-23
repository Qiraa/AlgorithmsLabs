#pragma once

#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class ShortestPathAlgorithm {
    public: 
    virtual unordered_map<long, Edge> findShortestPath(
        Node& from, 
        Node& to, 
        unordered_map<long, vector<Edge>>& incidence_map
    ) = 0;
    virtual ~ShortestPathAlgorithm() { };
};