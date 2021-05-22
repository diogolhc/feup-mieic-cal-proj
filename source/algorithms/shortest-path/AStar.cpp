#include <iostream>
#include "AStar.h"


AStar::AStar(Graph *graph, Vertex *source, Vertex *dest) : graph(graph), s(source), d(dest), ran(false), vertexViewedCount(0) {}


void AStar::run() {

    cout << "Edges size " << this->graph->getEdges().size() << endl;

    this->vertexViewedCount = 0;

    if (this->s == nullptr || this->d == nullptr)
        return;

    std::function<double(const Vertex*)> prevHeuristic = Vertex::heuristic;
    Coordinates destCoords = this->d->getCoordinates();
    Vertex::heuristic = [destCoords](const Vertex*v) {return v->getCoordinates().dist(destCoords);};


    for (Vertex* vertex : graph->getVertexSet()){
        auto vertexDist = dist.find(vertex);
        if (vertexDist != dist.end()) vertexDist->second = INF;
        else dist.insert(pair<Vertex *, double>(vertex, INF));
        vertex->setDist(INF);

        vertex->setVisited(false);

        vertex->setQueueIndex(0);

        for (Edge * edge : vertex->getOutgoing()){
            edge->setPassedShortestPath(false);
        }

        auto vertexPath = path.find(vertex);
        if (vertexPath != path.end()) {
            vertexPath->second.first = nullptr;
            vertexPath->second.second = nullptr;
        }
        else path.insert(pair<Vertex *, pair<Edge*, Vertex*> >(vertex, pair<Edge*, Vertex*>(nullptr, nullptr)));
    }

    Vertex * v = s;

    dist.at(v) = 0;
    v->setDist(0);

    MutablePriorityQueue<Vertex> vertexQueue;
    vertexQueue.insert(v);

    while(!vertexQueue.empty()){
        v = vertexQueue.extractMin();
        this->vertexViewedCount++;
        v->setVisited(true);

        if (v->getId() == d->getId()) {
            break;
        }

        for (Edge * edge : v->getOutgoing()) {
            Vertex * destinationVertex = edge->getDest();

            if (dist.at(destinationVertex) > dist.at(v) + edge->getWeight()){
                dist.at(destinationVertex) = dist.at(v) + edge->getWeight();
                destinationVertex->setDist(v->getDist() + edge->getWeight());
                path.at(destinationVertex) = pair<Edge*, Vertex*>(edge, v);

                destinationVertex->setDist(dist.at(destinationVertex));

                vertexQueue.insertOrDecreaseKey(destinationVertex);
            }
        }
    }

    Vertex::heuristic = prevHeuristic;
    this->ran = true;
}

std::list<Edge *> AStar::getPath() const {
    std::list<Edge *> res;

    if (!this->ran)
        return res;

    int count = 0;

    Vertex *v = d;
    while(v->getId() != s->getId()) {

        cout << "Here bitch " << count++ << " " << path.size() << endl;

        pair<Edge*, Vertex*> p = path.at(v);
        if (p.first == nullptr) {
            return std::list<Edge *>(); //No path found
        }
        res.push_front(p.first);
        p.first->setPassedShortestPath(true);

        v = p.second;
    }

    return res;
}

size_t AStar::getVertexViewedCount() const {
    return this->vertexViewedCount;
}
