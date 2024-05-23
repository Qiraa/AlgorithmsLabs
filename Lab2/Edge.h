#pragma once
#include <iostream>

class Edge {
    public:
    long u;
    long v;

    double ux;
    double uy;

    double vx;
    double vy;

    long dist;

    Edge(long u, long v) : u(u), v(v), ux(-1), uy(-1), vx(-1), vy(-1) {}
    Edge(): Edge(-1, -1) { }
};