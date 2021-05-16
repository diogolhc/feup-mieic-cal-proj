#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <unordered_set>
#include <limits>

#include "MutablePriorityQueue.h"

#define INF std::numeric_limits<size_t>::max()


class Vertex;
class Edge;
class Graph;
struct VertexPFunc;

typedef unordered_set<Vertex *, VertexPFunc, VertexPFunc> VertexSet;

struct Coordinates {
    double lat;
    double lon;
    double dist(Coordinates coordinates);
};

struct XY {
    double x;
    double y;
    double dist(XY xy);
};


class Vertex {
    std::vector<Edge *> outgoing;
    std::vector<Edge *> incoming;
    Coordinates coordinates;
    XY xy;

    //Nearest Neighbor
    bool isApplicationCenter;
    bool ACVisited;

    // Kosaraju and Tarjan elements needed
    // TODO its ok to put this elements here? Because its just for the Algorithms
    int id;
    int low;
    bool onStack;
    size_t scc;

    bool visited;  // for path finding
    Edge *path; // for path finding
    size_t dist;   // for path finding
    int queueIndex = 0; // required by MutablePriorityQueue

    Vertex(size_t in);
    void addEdge(Edge *e);
    bool operator<(const Vertex & vertex) const; // required by MutablePriorityQueue

public:

    void setCoordinates(Coordinates coordinates);
    Coordinates getCoordinates();
    bool getVisited() const;
    void setVisited(bool visited);
    void setXY(XY xy);
    XY getXY();
    size_t getSCC();
    void setSCC(size_t scc);
    size_t getId() const;
    std::vector<Edge *> getIncoming() const;
    std::vector<Edge *> getOutgoing() const;
    bool getIsApplicationCenter() const;
    bool getACVisited() const;
    void setACVisited(bool value);
    friend class Graph;
    friend class MutablePriorityQueue<Vertex>;
};


class Edge {
    Vertex * orig;
    Vertex * dest;
    double weight;

    Edge(Vertex *o, Vertex *d, double weight);

public:
    Vertex * getDest() const;
    Vertex * getOrig() const;
    size_t getWeight() const;
    friend class Graph;
    friend class Vertex;
};


struct VertexPFunc {
    size_t operator() (Vertex const* v) const {
        return v->getId();
    }

    bool operator() (Vertex const* v1, Vertex const* v2) const {
        return v1->getId() == v2->getId();
    }
};

class Graph {
    VertexSet vertexSet;

public:

    Vertex* findVertex(size_t id) const;
    VertexSet getVertexSet() const;
    // TODO vv maybe change the way it's being done and saved...
    vector<Edge *> getEdges() const;
    Vertex *addVertex(size_t id);
    Edge *addEdge(Vertex *sourc, Vertex *dest, double weight);
    Edge *addEdge(size_t sourc, size_t dest, double weight);
};

#endif /* GRAPH_H_ */