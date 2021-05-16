#ifndef SOURCE_MULTISOURCEDIJKSTRA_H
#define SOURCE_MULTISOURCEDIJKSTRA_H

#include <unordered_map>
#include <set>

#include "../../Graph.h"


class MultiSourceDijkstra {
private:
    vector<Vertex *> starts;
    Graph * graph;
    unordered_map<Vertex *, double> dist;
    unordered_map<Vertex *, Vertex *> path;
    unordered_map<std::size_t, std::set<size_t>> clusters;

public:
    MultiSourceDijkstra(Graph *g, const vector<Vertex *> &starts);
    void run();
    unordered_map<std::size_t, std::set<size_t>> & getClusters();
};


#endif //SOURCE_MULTISOURCEDIJKSTRA_H
