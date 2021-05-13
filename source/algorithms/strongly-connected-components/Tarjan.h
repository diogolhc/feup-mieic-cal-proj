#ifndef SOURCE_TARJAN_H
#define SOURCE_TARJAN_H

#include "../../Graph.h"
#include <stack>

class Tarjan {
private:
    void DFS(Graph &g, Vertex* s, stack<Vertex*> &stack, int &sccCount, int &id, vector<vector<int>> &scc);

public:
    vector<vector<int>> tarjan(Graph &g);

};


#endif //SOURCE_TARJAN_H
