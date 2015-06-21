#ifndef OBJECT_H_
#define OBJECT_H_

#include "util/Vector.h"
#include "util/Matrix.h"

#include <vector>
#include <iostream>

struct Vertex
{
    Vector pos; // position
    Matrix Q;   // Q Matrix

    bool removed; // removed?
    int time; // latest update time
    
    std::vector<int> planes; // indexes of neighbor planes
    std::vector<int> vertices; // indexes of neighbor vertices

    Vertex(double x, double y, double z)
        : pos(Vector(x, y, z)), removed(false) {}

    friend std::ostream& operator << (std::ostream& os, const Vertex& v);
};

struct Plane
{
    int a, b, c; // indexes of three vertices
    double args[4]; // 4 args in equation: ax + by + cz + d = 0
    Matrix K; // K = args^T * args

    bool removed; // removed?
    int time; // latest update time

    Plane(int a, int b, int c)
        : a(a), b(b), c(c), removed(false) {}

    void swap(int i, int j)
    {
        if (a == i) a = j;
        if (b == i) b = j;
        if (c == i) c = j;
    }

    friend std::ostream& operator << (std::ostream& os, const Plane& p);
};

struct Object
{
    Object()
        : n_vertices(0), n_planes(0) {}

    // obj file I/O
    void load(const std::string& file);
    void dump(const std::string& file);

    // updaters
    void updatePlaneArgs(Plane& p);
    void updateVertexNeighbors();

    // hard delete soft-removed elements
    void rebuild();

    // containers
    std::vector<Vertex> vertices;
    std::vector<Plane> planes;

    // counters
    int n_vertices;
    int n_planes;

    // debug
    void print();
};

#endif // OBJECT_H_