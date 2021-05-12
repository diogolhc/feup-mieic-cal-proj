#ifndef SOURCE_KOSARAJU_H
#define SOURCE_KOSARAJU_H

#include <iostream>
#include <stack>
#include "../Graph.h"

using namespace std;

vector<vector<Vertex*>> kosaraju(Graph &g);

void DFS1(Graph &g, Vertex* s, stack<Vertex*> &stack);

void DFS2(Graph &g, int component, Vertex *s);

void DFS1(Graph &g, Vertex* s, stack<Vertex*> &stack) {

    s->setVisited(true);
    for (Edge *edge : s->getOutgoing()) {
        Vertex *dest = edge->dest;
        if (!dest->visited) {
            DFS1(g, dest, stack);
        }
    }
    stack.push(s);
}

// g here is transposed
void DFS2(Graph &g, int component, Vertex *s, vector<vector<Vertex<T>*>> &scc) {
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

Graph getTranspose(Graph &g) {
    Graph t;
    for (Vertex *v : g.getVertexSet()) {
        t.addVertex(v->info);
        for (Edge * edge : v->getOutgoing()) {
            Vertex* dest = edge->dest;
            t.addVertex(dest->info);
            t.addEdge(dest->info, v->info, 0, 0);
        }
    }
    return t;
}

vector<vector<Vertex*>> kosaraju(Graph &g) {
    vector<vector<Vertex*>> scc;
    stack<Vertex*> stack;
    int component = 0;

    for ( Vertex *v : g.getVertexSet()) {
        v->visited = false;
    }

    for (Vertex *v : g.getVertexSet()) {
        if (!v->visited) {
            DFS1(g, v, stack);
        }
    }

    Graph t = getTranspose(g);

    for (Vertex* v : t.getVertexSet()) {
        v->visited = false;
    }

    while( !stack.empty() ) {
        Vertex *v = stack.top();
        stack.pop();

        if (!v->visited) {
            DFS2(t, component, v, scc);
        }
        component++;
    }

    return scc;
}

#endif //SOURCE_KOSARAJU_H
