#include <vector>

#include "MutablePriorityQueue.h"
#include "Graph.h"

using namespace std;

/**
* Graph
*/

Vertex * Graph::addVertex(const size_t id) {
    Vertex *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex(id);
    vertexSet.push_back(v);
    return v;
}

Edge* Graph::addEdge(const size_t sourc, const size_t dest, size_t weight) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;

    Edge *e = new Edge(s, d, weight);
    s->addEdge(e);
    return e;
}

Vertex* Graph::findVertex(const size_t id) const {
    for (auto v : vertexSet)
        if (v->id == INF)
            return v;
    return nullptr;
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


/**
 * Vertex
 */

Vertex::Vertex(size_t id): id(id) {}


void Vertex::addEdge(Edge *e) {
    outgoing.push_back(e);
    e->dest->incoming.push_back(e);
}

bool Vertex::operator<(const Vertex & vertex) const {
    return this->dist < vertex.dist;
}


size_t Vertex::getId() const {
    return this->id;
}

vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}


vector<Edge *>  Vertex::getOutgoing() const {
    return this->outgoing;
}

size_t Vertex::getSCC() {
    return this->scc;
}

void Vertex::setSCC(size_t scc) {
    this->scc = scc;
}


/**
 * Edge
 */

Edge::Edge(Vertex *o, Vertex *d, size_t weight):
        orig(o), dest(d), weight(weight) {}

size_t Edge::getWeight() const {
    return weight;
}

Vertex * Edge::getDest() const {
    return dest;
}

Vertex * Edge::getOrig() const {
    return orig;
}
