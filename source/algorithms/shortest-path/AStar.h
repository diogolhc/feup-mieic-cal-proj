#ifndef SOURCE_ASTAR_H
#define SOURCE_ASTAR_H

#include "../../Graph.h"
#include <list>


class AStar {
private:
    Graph * graph;
    Vertex *s;
    Vertex *d;

    bool ran;
    unordered_map<Vertex *, double> dist;
    unordered_map<Vertex *, std::pair<Edge*, Vertex *> > path;
    size_t vertexViewedCount;
public:
    AStar(Graph *graph, Vertex *source, Vertex *dest);
    void run();
    std::list<Edge *> getPath() const;
    size_t getVertexViewedCount() const;
};


#endif //SOURCE_ASTAR_H
