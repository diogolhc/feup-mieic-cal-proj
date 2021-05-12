#ifndef SOURCE_KOSARAJU_H
#define SOURCE_KOSARAJU_H

#include <iostream>
#include <stack>
#include "../Graph.h"

using namespace std;

template <class T>
vector<vector<Vertex<T>*>> kosaraju(Graph<T> &g);

template <class T>
void DFS1(Graph<T> &g, Vertex<T>* s, stack<Vertex<T>*> &stack);

template <class T>
void DFS2(Graph<T> &g, int component, Vertex<T> *s);

template <class T>
void DFS1(Graph<T> &g, Vertex<T>* s, stack<Vertex<T>*> &stack) {
    s->visited = true;
    for (Edge<T> *edge : s->getOutgoing()) {
        Vertex<T> *dest = edge->dest;
        if (!dest->visited) {
            DFS1(g, dest, stack);
        }
    }
    stack.push(s);
}

// g here is transposed
template <class T>
void DFS2(Graph<T> &g, int component, Vertex<T> *s, vector<vector<Vertex<T>*>> &scc) {
    s->visited = true;
    s->scc = component;
    scc[component].push_back(s);
    for (Edge<T>* edge : s->getOutgoing()) {
        Vertex<T>* dest = edge->dest;
        if (!dest->visited) {
            DFS2(g, component, s, scc);
        }
    }
}

template <class T>
Graph<T> getTranspose(Graph<T> &g) {
    Graph<T> t;
    for (Vertex<T> *v : g.getVertexSet()) {
        t.addVertex(v->info);
        for (Edge<T> * edge : v->getOutgoing()) {
            Vertex<T>* dest = edge->dest;
            t.addVertex(dest->info);
            t.addEdge(dest->info, v->info, 0, 0);
        }
    }
    return t;
}

template <class T>
vector<vector<Vertex<T>*>> kosaraju(Graph<T> &g) {
    vector<vector<Vertex<T>*>> scc;
    stack<Vertex<T>*> stack;
    int component = 0;

    for ( Vertex<T> *v : g.getVertexSet()) {
        v->visited = false;
    }

    for (Vertex<T> *v : g.getVertexSet()) {
        if (!v->visited) {
            DFS1(g, v, stack);
        }
    }

    Graph<T> t = getTranspose(g);

    for (Vertex<T>*v : t.getVertexSet()) {
        v->visited = false;
    }

    while( !stack.empty() ) {
        Vertex<T> *v = stack.top();
        stack.pop();

        if (!v->visited) {
            DFS2(t, component, v, scc);
        }
        component++;
    }

    return scc;
}

#endif //SOURCE_KOSARAJU_H
