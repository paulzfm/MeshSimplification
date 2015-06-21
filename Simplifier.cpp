#include "Simplifier.h"

Simplifier::Simplifier(const std::string& input, const float percentage)
{
    std::cout << "### Loading " << input <<  "...\n";
    _obj.load(input);
    _target = int(_obj.planes.size() * percentage);
    std::cout << "### Target planes: " << _target 
              << " (" << 100 * (float)_target / _obj.planes.size() << "%)"<<  "\n";
}

void Simplifier::output(const std::string& output)
{
    std::cout << "### Saving " << output <<  "...\n";
    _obj.dump(output);

    // try load this file again to validate any errors
    std::cout << "### Validating " << output <<  "...\n";
    _obj.load(output);
    std::cout << "### Done\n";
}

void Simplifier::simplify()
{
    std::cout << "### Simplifing...\n";

    computeQMatrix();
    buildQueue();

    _current_time = 0;

    // _obj.print();

    while (_obj.n_planes > _target) {
        Pair pair;
        do {
            pair = _queue.top();
            _queue.pop();
        } while (_obj.vertices[pair.i].removed || _obj.vertices[pair.j].removed ||
                 pair.i == pair.j || 
                 pair.time < _obj.vertices[pair.i].time + _obj.vertices[pair.j].time);

        int i = pair.i;
        int j = pair.j;
        _obj.vertices[i].pos = _obj.vertices[j].pos = pair.mid;

        // printf("Pair: %d, %d\n", i, j);

        removePlanes(i, j);
        updateEdges(i, j);
        updatePlanes(i);
        updateQMatrix(i);
        for (const auto& v : _obj.vertices[i].vertices) {
            updateQMatrix(v);
        }
        updateQueue(i);
        for (const auto& v : _obj.vertices[i].vertices) {
            updateQueue(v);
        }

        // _obj.print();

        ++_current_time;
        if (_current_time % 1000 == 0) { // hard remove
            _obj.rebuild();
        }
    }
}

void Simplifier::computeQMatrix()
{
    // Q(v) = \sum_{p \in planes(v)} K_p
    for (auto& v : _obj.vertices) {
        for (const auto& i : v.planes) {
            v.Q += _obj.planes[i].K;
        }
    }
}

void Simplifier::buildQueue()
{
    int n = _obj.vertices.size();
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < _obj.vertices[i].vertices.size(); ++k) {
            int j = _obj.vertices[i].vertices[k];
            _queue.push(Pair(i, j, _obj.vertices[i], _obj.vertices[j]));
        }
    }
}

void Simplifier::removePlanes(int i, int j)
{
    // remove i's neighbors
    for (const auto& p : _obj.vertices[i].planes) {
        if (_obj.planes[p].removed) { // already removed
            continue;
        }

        if (_obj.planes[p].a == j || _obj.planes[p].b == j ||
            _obj.planes[p].c == j) { // j is on this plane
            _obj.planes[p].removed = true;
            --_obj.n_planes;
        }
    }

    // consider j's neighbors
    for (const auto& p : _obj.vertices[j].planes) {
        if (!_obj.planes[p].removed) { // if this plane is not removed
            _obj.planes[p].swap(j, i);
            _obj.vertices[i].planes.push_back(p);
        }
    }

    // remove j
    _obj.vertices[j].removed = true;
    --_obj.n_vertices;
    _obj.vertices[j].planes.clear();
}

void Simplifier::updateEdges(int i, int j)
{
    for (const auto& v : _obj.vertices[j].vertices) {
        if (!_obj.vertices[v].removed && !has(i, _obj.vertices[v].vertices)) { // not connect with i
            for (auto& n : _obj.vertices[v].vertices) {
                if (n == j) { // change edges who linked with j to i
                    n = i;
                    if (!has(v, _obj.vertices[i].vertices)) {
                        _obj.vertices[i].vertices.push_back(v);
                    }
                }
            }
        }
    }

    _obj.vertices[j].vertices.clear();
}

void Simplifier::updatePlanes(int i)
{
    for (const auto& p : _obj.vertices[i].planes) {
        if (!_obj.planes[p].removed) {
            _obj.updatePlaneArgs(_obj.planes[p]);
        }
    }
}

void Simplifier::updateQMatrix(int i)
{
    _obj.vertices[i].Q = Matrix();

    // update Q(i)
    for (const auto& p : _obj.vertices[i].planes) {
        if (!_obj.planes[p].removed) {
            _obj.vertices[i].Q += _obj.planes[p].K;
        }
    }
}

void Simplifier::updateQueue(int i)
{
    _obj.vertices[i].time = _current_time;
    for (const auto& v : _obj.vertices[i].vertices) {
        if (!_obj.vertices[v].removed) {
            _queue.push(Pair(i, v, _obj.vertices[i], _obj.vertices[v]));
        }
    }
}
