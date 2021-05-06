#ifndef SOURCE_KOSARAJU_H
#define SOURCE_KOSARAJU_H

#include <iostream>
#include <stack>

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
            DFS1(g, dest);
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
    for (Vertex<T>*v : g.getVertexSet()) {
        v->visited = false;
    }

    while( !stack.empty() ) {
        Vertex<T> *v = stack.top();
        stack.pop();

        if (!v->visited) {
            DFS2(g, component, v);
        }
        component++;
    }

    return scc;
}

#endif //SOURCE_KOSARAJU_H
