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
    void DFS2(Graph &g, int component, Vertex *s);
    Graph getTranspose(Graph &g);
    vector<int> sccCountMap;
public:
    vector<int> getMap() const;
    void run(Graph &g);
};


#endif //SOURCE_KOSARAJU_H
