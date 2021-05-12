#include "Graph.h"

using namespace std;

/**
* Graph
*/

/**
 * @param v Vertex to insert
 * @return false if vertex was already on Graph, true otherwise
 */
bool Graph::addVertexPointer(Vertex *v) {
    Vertex *t = findVertex(v->id);
    if (t != nullptr)
        return false;
    vertexSet.push_back(v);
    return true;
}

Vertex * Graph::addVertex(size_t id) {
    Vertex *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex(id);
    vertexSet.push_back(v);
    return v;
}

Edge* Graph::addEdge(size_t sourc, size_t dest, size_t weight) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;

    Edge *e = new Edge(s, d, weight);
    s->addEdge(e);
    return e;
}

Vertex* Graph::findVertex(size_t id) const {
    for (auto v : vertexSet)
        if (v->id == id)
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


void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

bool Vertex::getVisited() const {
    return this->visited;
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
