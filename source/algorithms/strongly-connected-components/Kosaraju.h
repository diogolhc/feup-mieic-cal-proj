#ifndef SOURCE_KOSARAJU_H
#define SOURCE_KOSARAJU_H

#include <vector>
#include <stack>
#include <map>
#include "../../Graph.h"

using namespace std;

class Kosaraju {
private:
    void DFS1(Graph &g, Vertex* s, stack<Vertex*> &stack);
    void DFS2(Graph &g, size_t component, Vertex *s);
    Graph getTranspose(Graph &g);
    vector<size_t> sccCountMap;
public:
    vector<size_t> getMap() const;
    void run(Graph &g);
};


#endif //SOURCE_KOSARAJU_H