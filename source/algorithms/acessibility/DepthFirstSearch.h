#ifndef SOURCE_DEPTHFIRSTSEARCH_H
#define SOURCE_DEPTHFIRSTSEARCH_H

#include "../../Graph.h"

class DepthFirstSearch {
public:
    void run(Graph &g);
    void DFS_VISIT(Graph &g, Vertex* v);
};


#endif //SOURCE_DEPTHFIRSTSEARCH_H
