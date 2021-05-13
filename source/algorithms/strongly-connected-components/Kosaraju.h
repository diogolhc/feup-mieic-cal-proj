#ifndef SOURCE_KOSARAJU_H
#define SOURCE_KOSARAJU_H

#include <vector>
#include <stack>
#include "../../Graph.h"

using namespace std;

class Kosaraju {
private:
    void DFS1(Graph &g, Vertex* s, stack<Vertex*> &stack);
    void DFS2(Graph &g, int component, Vertex *s);
    Graph getTranspose(Graph &g);

public:
    void kosaraju(Graph &g);
};


#endif //SOURCE_KOSARAJU_H
