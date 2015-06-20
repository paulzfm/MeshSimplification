#ifndef SIMPLIFIER_H_
#define SIMPLIFIER_H_

#include "Object.h"

#include <string>
#include <queue>
#include <algorithm>

struct Pair
{
    int i, j; // indexes of vertices
    double delta; // cost of merge
    Vector mid; // middle point

    bool removed; // removed?
    int time; // latest update time

    Pair() {}

    Pair(int i, int j, const Vertex& a, const Vertex& b)
        : i(i), j(j), removed(false), delta(0.0)
    {
        mid = (a.pos + b.pos) / 2;
        time = a.time + b.time;
        
        Matrix Q = a.Q + b.Q;
        double tmp[4] = {mid.x, mid.y, mid.z, 1.0};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delta += Q.x[i][j] * tmp[i] * tmp[j];
            }
        }
    }

    friend bool operator < (const Pair& a, const Pair& b)
    {
        return a.delta > b.delta;
    }
};

class Simplifier
{
public:
    Simplifier(const std::string& input, const float percentage);

    // just call this to run mesh simplification
    void simplify();

    // call this to save result as .obj after mesh simplification
    void output(const std::string& output);

private:
    Object _obj; // object
    int _target; // number of planes
    int _current_time; // current time
    std::priority_queue<Pair> _queue; // pairs

    void computeQMatrix();
    void buildQueue();
    void removePlanes(int i, int j);
    void updateEdges(int i, int j);
    void updatePlanes(int i);
    void updateQMatrix(int i);
    void updateQueue(int i);
};

// helper function
template <typename T>
inline bool has(const T& e, std::vector<T> v)
{
    return std::find(v.begin(), v.end(), e) != v.end();
}

#endif // SIMPLIFIER_H_