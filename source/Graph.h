#ifndef GRAPH_H_
#define GRAPH_H_

#include <limits>
#include <unordered_set>
#include <vector>
#include <functional>

#include "agents/Truck.h"
#include "MutablePriorityQueue.h"

#define INF std::numeric_limits<double>::max()

class Vertex;
class Edge;
class Graph;
struct VertexPFunc;

typedef unordered_set<Vertex *, VertexPFunc, VertexPFunc> VertexSet;

enum VertexType {
    STORAGE_CENTER,
    NOT_USED_SC,
    APPLICATION_CENTER,
    NOT_REACHABLE_AC,
    NONE
};

struct Coordinates {
    double lat;
    double lon;
    double dist(Coordinates coordinates);
};


class Vertex {
    std::vector<Edge *> outgoing;
    std::vector<Edge *> incoming;
    Coordinates coordinates;

    //MultiDijkstra
    size_t cluster;

    //Nearest Neighbor
    VertexType type;
    bool ACVisited;

    // Kosaraju and Tarjan elements needed
    int id;
    int low;
    bool onStack;
    size_t scc;
    bool visited;  // for path finding
    Edge *path; // for path finding
    double dist;   // for path finding
    int queueIndex = 0; // required by MutablePriorityQueue

    Vertex(size_t in);
    void addEdge(Edge *e);
    bool operator<(const Vertex & vertex) const; // required by MutablePriorityQueue

public:

    //AStar
    static std::function<double(const Vertex*)> heuristic;

    void setCoordinates(Coordinates coordinates);
    Coordinates getCoordinates() const;
    bool getVisited() const;
    void setVisited(bool visited);
    size_t getSCC();
    void setSCC(size_t scc);
    size_t getId() const;
    VertexType getType() const;
    void setType(VertexType type);
    std::vector<Edge *> getIncoming() const;
    std::vector<Edge *> getOutgoing() const;
    bool getIsApplicationCenter() const;
    bool getACVisited() const;
    void setACVisited(bool value);
    double getDist() const;
    void setDist(double value);
    void setQueueIndex(int index);
    void setCluster(size_t cluster);
    size_t getCluster() const;
    friend class Graph;
    friend class MutablePriorityQueue<Vertex>;
};


class Edge {
    Vertex * orig;
    Vertex * dest;
    double weight;
    bool passedShortestPath;
    vector<Truck *> passedTrucks;
    Edge(Vertex *o, Vertex *d, double weight);

public:
    Vertex * getDest() const;
    Vertex * getOrig() const;
    size_t getWeight() const;
    void setPassedShortestPath(bool passed);
    bool getPassedShortestPath() const;
    std::vector<Truck *> & getPassedTrucks();
    void passTruck(Truck * truck);
    void removeTruck(Truck * truck);
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
    ~Graph();

    Vertex* findVertex(size_t id) const;
    VertexSet getVertexSet() const;
    // TODO vv maybe change the way it's being done and saved...
    vector<Edge *> getEdges() const;
    Vertex *addVertex(size_t id);
    Edge *addEdge(Vertex *sourc, Vertex *dest, double weight);
    Edge *addEdge(size_t sourc, size_t dest, double weight);
};

#endif /* GRAPH_H_ */