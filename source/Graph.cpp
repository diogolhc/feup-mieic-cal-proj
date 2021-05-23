#include <vector>
#include <math.h>
#include <iostream>

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

Graph::~Graph() {
    for (Edge *e : this->getEdges()) {
        delete(e);
    }

    for (Vertex *v : this->vertexSet) {
        delete(v);
    }
}


/**
 * Vertex
 */

std::function<double(const Vertex*)> Vertex::heuristic = [](const Vertex *v) {return 0;};

Vertex::Vertex(size_t id): id(id), type(NONE), cluster(0) {}


void Vertex::addEdge(Edge *e) {
    outgoing.push_back(e);
    e->dest->incoming.push_back(e);
}

bool Vertex::operator<(const Vertex & vertex) const {
    return (this->dist + Vertex::heuristic(this)) < (vertex.dist + Vertex::heuristic(&vertex));
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

VertexType Vertex::getType() const {
    return this->type;
}

void Vertex::setType(VertexType type) {
    this->type = type;
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

Coordinates Vertex::getCoordinates() const {
    return this->coordinates;
}

bool Vertex::getIsApplicationCenter() const{
    return this->type == APPLICATION_CENTER;
}

bool Vertex::getACVisited() const{
    return this->ACVisited;
}

void Vertex::setACVisited(bool value) {
    this->ACVisited = value;
}

double Vertex::getDist() const{
    return this->dist;
}

void Vertex::setDist(double value) {
    this->dist = value;
}

void Vertex::setQueueIndex(int index) {
    this->queueIndex = index;
}

void Vertex::setCluster(size_t cluster) {
    this->cluster = cluster;
}

size_t Vertex::getCluster() const {
    return this->cluster;
}


/**
 * Edge
 */

Edge::Edge(Vertex *o, Vertex *d, double weight):
        orig(o), dest(d), weight(weight), passedShortestPath(false) {}

size_t Edge::getWeight() const {
    return weight;
}

Vertex * Edge::getDest() const {
    return dest;
}

Vertex * Edge::getOrig() const {
    return orig;
}

void Edge::setPassedShortestPath(bool passed) {
    this->passedShortestPath = passed;
}

bool Edge::getPassedShortestPath() const {
    return this->passedShortestPath;
}

void Edge::passTruck(Truck *truck) {
    this->passedTrucks.push_back(truck);
    truck->addEdge(this);
}

vector<Truck *> & Edge::getPassedTrucks(){
    return this->passedTrucks;
}

void Edge::removeTruck(Truck * truck) {
    auto iter = find(passedTrucks.begin(), passedTrucks.end(), truck);

    if (iter == passedTrucks.end()) return;

    this->passedTrucks.erase(iter);
}

void Edge::resetTrucks() {
    this->passedTrucks.clear();
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
