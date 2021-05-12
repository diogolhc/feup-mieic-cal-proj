#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <limits>

#include "MutablePriorityQueue.h"

constexpr auto INF = std::numeric_limits<double>::max();

class Vertex;
class Edge;
class Graph;


class Graph {
    vector<Vertex *> vertexSet;

public:
    Vertex* findVertex(size_t id) const;
    vector<Vertex *> getVertexSet() const;
    Vertex *addVertex(size_t id);
    Edge *addEdge(size_t sourc, size_t dest, size_t weight);
};


class Vertex {
    std::vector<Edge *> outgoing;
    std::vector<Edge *> incoming;

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

    size_t getSCC();
    void setSCC(size_t scc);
    size_t getId() const;
	std::vector<Edge *> getIncoming() const;
	std::vector<Edge *> getOutgoing() const;
	bool getVisited() const;
	void setVisited(bool visited);
	friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
};


class Edge {
    Vertex * orig;
    Vertex * dest;
	size_t weight;

    Edge(Vertex *o, Vertex *d, size_t weight);

public:
	friend class Graph;
	friend class Vertex;
};

#endif /* GRAPH_H_ */
