#include "Tarjan.h"
#include <stack>
/*
void DFS(Graph &g, Vertex* s, stack<Vertex*> &stack, int &sccCount, int &id, vector<vector<int>> &scc) {
    stack.push(s);
    s.setId = id;
    id++;
    s->low = s->id;
    s->onStack = true;

    for (Edge* edge : s->getOutgoing()) {
        Vertex *dest = edge->getDest();
        if ( dest->getId() == -1 ) {     // NULL
            DFS(g, dest, stack, sccCount, id, scc);
        }
        if ( dest->onStack ) {
            s->low = min(s->low, dest->low);
        }
    }

    if ( s->low == s->id ) {
        while (true) {
            Vertex<T>* v = stack.top();
            stack.pop();
            if (v == s) break;
            v->onStack = false;
            v->low = s->id;
            scc[sccCount].push_back(v);
        }
        scc[sccCount].push_back(s->getId());
        sccCount++;
    }
}


vector<vector<int>> tarjan(Graph &g) {
    vector<vector<int>> scc;
    stack<Vertex*> stack;
    int sccCount = 0;
    int id = 0;


    for (Vertex* u : g.getVertexSet()) {
        u->id = -1;     // NULL
        u->scc = -1;    // NULL
    }

    for (Vertex* u : g.getVertexSet()) {
        if (u->getId() == -1) {   // NULL
            DFS1(g, u, stack, sccCount, id, scc);
        }
    }

    return scc;
}*/
