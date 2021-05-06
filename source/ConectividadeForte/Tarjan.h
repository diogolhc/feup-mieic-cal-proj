#ifndef SOURCE_TARJAN_H
#define SOURCE_TARJAN_H

#include <iostream>
#include <stack>
#include <algorithm>    // std::min
#include "../Graph.h"

using namespace std;

template <class T>
vector<vector<Vertex<T>*>> tarjan(Graph<T> &g);

template <class T>
void DFS(Graph<T> &g, Vertex<T>* s, stack<Vertex<T>*> &stack, int &sccCount, int &id, vector<vector<Vertex<T>*>> &scc);


template <class T>
void DFS(Graph<T> &g, Vertex<T>* s, stack<Vertex<T>*> &stack, int &sccCount, int &id, vector<vector<Vertex<T>*>> &scc) {
    stack.push(s);
    s->id = id;
    id++;
    s->low = s->id;
    s->onStack = true;

    for (Edge<T>* edge : s->getOutgoing()) {
        Vertex<T> *dest = edge->dest;
        if ( dest->id == -1 ) {     // NULL
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
        scc[sccCount].push_back(s);
        sccCount++;
    }
}

template <class T>
vector<vector<Vertex<T>*>> tarjan(Graph<T> &g) {
    vector<vector<Vertex<T>*>> scc;
    stack<Vertex<T>*> stack;
    int sccCount = 0;
    int id = 0;


    for (Vertex<T>* u : g.getVertexSet()) {
        u->id = -1;     // NULL
        u->scc = -1;    // NULL
    }

    for (Vertex<T>* u : g.getVertexSet()) {
        if (u->id == -1) {   // NULL
            DFS1(g, u, stack, sccCount, id, scc);
        }
    }

    return scc;
}

#endif //SOURCE_TARJAN_H
