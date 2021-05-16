#include "BreathFirstSearch.h"

#include <queue>
#include <iostream>

using namespace std;

void BreathFirstSearch::run(Graph &g, Vertex *source) {
    if (source == nullptr) {
        cout << "Invalid source" << endl;
        return;
    }
    for (Vertex *v : g.getVertexSet()) {
        v->setVisited(false);
    }

    source->setVisited(true);

    queue<Vertex *> q;
    q.push(source);

    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();

        for (Edge *e : v->getOutgoing()) {
            Vertex *w = e->getDest();
            if (!w->getVisited()) {
                w->setVisited(true);
                q.push(w);
            }
        }
    }
}

