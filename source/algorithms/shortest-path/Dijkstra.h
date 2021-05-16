#ifndef SOURCE_DIJKSTRA_H
#define SOURCE_DIJKSTRA_H

#include "../../Graph.h"

#include <unordered_map>

class Dijkstra {
    Vertex * s;
    Graph * graph;
    unordered_map<Vertex *, double> dist;
    unordered_map<Vertex *, Vertex *> path;
public:
    void initialize(Graph * graph, int origin_id);
    void run();
    void changeOriginId(int origin_id);
    Vertex * getNearestAC(std::vector<size_t> application_center_ids);
    unordered_map<Vertex *, Vertex *> getPath() const;
};


#endif //SOURCE_DIJKSTRA_H
