#include <vector>
#include <math.h>

#include "MutablePriorityQueue.h"
#include "Graph.h"

using namespace std;

/**
* Graph
*/

Vertex * Graph::addVertex(size_t id) {
    Vertex *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex(id);
    vertexSet.insert(v);
    return v;
}

Edge* Graph::addEdge(Vertex *sourc, Vertex *dest, double weight) {
    if (sourc == nullptr || dest == nullptr)
        return nullptr;

    Edge *e = new Edge(sourc, dest, weight);
    sourc->addEdge(e);
    return e;
}

Edge* Graph::addEdge(size_t sourc, size_t dest, double weight) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;

    Edge *e = new Edge(s, d, weight);
    s->addEdge(e);
    return e;
}

Vertex* Graph::findVertex(size_t id) const {
    Vertex v = Vertex(id);
    VertexSet::const_iterator it = vertexSet.find(&v);
    if (it == vertexSet.end())
        return nullptr;
    return *it;
}

VertexSet Graph::getVertexSet() const {
    return vertexSet;
}

// maybe change latter for efficiency
vector<Edge *> Graph::getEdges() const {
    vector<Edge *> edges;
    for (Vertex *v : vertexSet) {
        edges.insert(edges.end(), v->outgoing.begin(), v->outgoing.end());
    }

    return edges;
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

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

bool Vertex::getVisited() const {
    return this->visited;
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

void Vertex::setCoordinates(Coordinates coordinates) {
    this->coordinates = coordinates;
}

Coordinates Vertex::getCoordinates() {
    return this->coordinates;
}

void Vertex::setXY(XY xy) {
    this->xy = xy;
}

XY Vertex::getXY() {
    return this->xy;
}


/**
 * Edge
 */

Edge::Edge(Vertex *o, Vertex *d, double weight):
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

/**
*  Dists:
*/

// https://stackoverflow.com/a/21623206
double Coordinates::dist(Coordinates coordinates) {
    double p = 0.017453292519943295;    // pi / 180
    double a = 0.5 - cos((coordinates.lat - this->lat) * p) / 2 +
               cos(this->lat * p) * cos(coordinates.lat * p) *
               (1 - cos((coordinates.lon - this->lon) * p)) / 2;
    return 12742 * asin(sqrt(a)) * 1000; // 2 * R; R = 6371 km // in meters
}

double XY::dist(XY xy) {
    return sqrt(pow(this->x - xy.x, 2) + pow(this->y - xy.y, 2));
}