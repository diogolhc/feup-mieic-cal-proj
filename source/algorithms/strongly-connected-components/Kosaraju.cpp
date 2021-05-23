#include "Kosaraju.h"
#include <iostream>

using namespace std;

void Kosaraju::DFS1(Graph *g, Vertex *s, stack<Vertex *> &stack) {
    s->setVisited(true);
    for (Edge *edge : s->getOutgoing()) {
        Vertex *dest = edge->getDest();
        if (!dest->getVisited()) {
            DFS1(g, dest, stack);
        }
    }
    stack.push(s);
}

void Kosaraju::DFS2(Graph *g, size_t component, Vertex *s) {
    s->setVisited(true);
    s->setSCC(component);
    sccCountMap[component]++;

    // Since we are going for the transposed, we search by the incoming
    // The dest of the incoming is the current Vertex
    // So the orig from the incoming is the dest from the transposed
    for (Edge* edge : s->getIncoming()) {
        Vertex* dest = edge->getOrig();
        if (!dest->getVisited()) {
            DFS2(g, component, dest);
        }
    }
}

void Kosaraju::run(Graph *g) {
    stack<Vertex*> stack;
    size_t component = 0;

    for ( Vertex *v : g->getVertexSet()) {
        v->setVisited(false);
        v->setSCC(0);
    }

    for (Vertex *v : g->getVertexSet()) {
        if (!v->getVisited()) {
            DFS1(g, v, stack);
        }
    }


    for (Vertex* v : g->getVertexSet()) {
        v->setVisited(false);
    }

    while( !stack.empty() ) {
        Vertex *v = stack.top();
        stack.pop();

        if (!v->getVisited()) {
            sccCountMap.push_back(0);
            DFS2(g, component, v);
            component++;
        }

    }
}

vector<size_t> Kosaraju::getMap() const {
    return this->sccCountMap;
}
