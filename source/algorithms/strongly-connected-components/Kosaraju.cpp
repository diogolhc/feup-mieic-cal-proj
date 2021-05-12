#include "Kosaraju.h"

void Kosaraju::DFS1(Graph &g, Vertex *s, stack<Vertex *> &stack) {
    s->setVisited(true);
    for (Edge *edge : s->getOutgoing()) {
        Vertex *dest = edge->getDest();
        if (!dest->getVisited()) {
            DFS1(g, dest, stack);
        }
    }
    stack.push(s);
}


// g here is transposed
void Kosaraju::DFS2(Graph &g, int component, Vertex *s) {
    s->setVisited(true);
    s->setSCC(component);

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


Graph Kosaraju::getTranspose(Graph &g) {
    Graph t;
    for (Vertex *v : g.getVertexSet()) {
        t.addVertex(v->getId());
        for (Edge * edge : v->getOutgoing()) {
            Vertex* dest = edge->getDest();
            t.addVertex(dest->getId());
            t.addEdge(dest->getId(), v->getId(), 0);
        }
    }
    return t;
}

void Kosaraju::kosaraju(Graph &g) {
    stack<Vertex*> stack;
    int component = 0;

    for ( Vertex *v : g.getVertexSet()) {
        v->setVisited(false);
    }

    for (Vertex *v : g.getVertexSet()) {
        if (!v->getVisited()) {
            DFS1(g, v, stack);
        }
    }

    Graph t = getTranspose(g);

    for (Vertex* v : g.getVertexSet()) {
        v->setVisited(false);
    }

    while( !stack.empty() ) {
        Vertex *v = stack.top();
        stack.pop();

        if (!v->getVisited()) {
            DFS2(g, component, v);
        }

        component++;
    }
}