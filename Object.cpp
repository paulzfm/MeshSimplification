#include "Object.h"
#include "util/SimpleObject.h"

void Object::load(const std::string& file)
{
    SimpleOBJ::CSimpleObject parser;
    parser.LoadFromObj(file.c_str());

    // load vertices
    for (int i = 0; i < parser.m_nVertices; ++i) {
        SimpleOBJ::Vec3f v = parser.m_pVertexList[i];
        vertices.push_back(Vertex(v[0], v[1], v[2]));
    }
    n_vertices = vertices.size();

    // load planes
    for (int i = 0; i < parser.m_nTriangles; ++i) {
        SimpleOBJ::Array<int, 3> t = parser.m_pTriangleList[i];
        planes.push_back(Plane(t[0], t[1], t[2]));
        updatePlaneArgs(planes[i]);
    }
    n_planes = planes.size();

    // find vertex neighbors after planes are loaded
    updateVertexNeighbors();
}

void Object::dump(const std::string& file)
{
    SimpleOBJ::CSimpleObject parser;

    parser.m_nVertices = n_vertices;
    parser.m_pVertexList = new SimpleOBJ::Vec3f[n_vertices];

    parser.m_nTriangles = n_planes;
    parser.m_pTriangleList = new SimpleOBJ::Array<int, 3>[n_planes];

    int i = 0;
    for (const auto& v : vertices) {
        parser.m_pVertexList[i] = SimpleOBJ::Vec3f(v.pos.x, v.pos.y, v.pos.z);
        ++i;
    }

    i = 0;
    for (const auto& p : planes) {
        parser.m_pTriangleList[i] = SimpleOBJ::Array<int, 3>(p.a, p.b, p.c);
        ++i;
    }

    parser.SaveToObj(file.c_str());
}

void Object::updatePlaneArgs(Plane& p)
{
    Vector n = (vertices[p.a].pos - vertices[p.b].pos).cross(
        vertices[p.b].pos - vertices[p.c].pos).normalize();

    // ax + by + cz + d = 0
    p.args[0] = n.x; // a
    p.args[1] = n.y; // b
    p.args[2] = n.z; // c
    p.args[3] = -n.dot(vertices[p.a].pos); // d

    // p * p^T
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            p.K.x[i][j] = p.args[i] * p.args[j];
        }
    }
}

void Object::updateVertexNeighbors()
{
    // first update neighbor planes
    for (int i = 0; i < n_planes; ++i) {
        vertices[planes[i].a].planes.push_back(i);
        vertices[planes[i].b].planes.push_back(i);
        vertices[planes[i].c].planes.push_back(i);
    }

    // then update neighbor vertices
    for (int i = 0; i < n_planes; ++i) {
        vertices[planes[i].a].vertices.push_back(planes[i].b);
        vertices[planes[i].b].vertices.push_back(planes[i].c);
        vertices[planes[i].c].vertices.push_back(planes[i].a);
    }
}

void Object::rebuild()
{

}

