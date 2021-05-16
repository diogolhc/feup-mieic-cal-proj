#include "DepthFirstSearch.h"

void DepthFirstSearch::run(Graph &g) {
    for (Vertex *v : g.getVertexSet()) {
        v->setVisited(false);
    }

    for (Vertex *v : g.getVertexSet()) {
        if (!v->getVisited()) {
            DFS_VISIT(g, v);
        }
    }
}

void DepthFirstSearch::DFS_VISIT(Graph &g, Vertex *v) {
    v->setVisited(true);

    for (Edge *e : v->getOutgoing()) {
        Vertex *w = e->getDest();
        if (!w->getVisited()) {
            DFS_VISIT(g, w);
        }
    }
}

