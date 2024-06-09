#pragma once

class Node {
    public:
    long id;
    double lon;
    double lat;

    double x;
    double y;

    Node(long id, double lon, double lat) : id(id), lon(lon), lat(lat) {}
};