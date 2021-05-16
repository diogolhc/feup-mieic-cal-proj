#include <iostream>
#include "MultiSourceDijkstra.h"


MultiSourceDijkstra::MultiSourceDijkstra(Graph *g, const vector<Vertex *> &starts) {
    this->graph = g;
    this->starts = starts;
}


void MultiSourceDijkstra::run() {
    VertexSet vertexSet = graph->getVertexSet();

    for (Vertex* vertex : vertexSet){

        auto vertexDist = dist.find(vertex);
        if (vertexDist != dist.end()) vertexDist->second = INF;
        else dist.insert(pair<Vertex *, double>(vertex, INF));

        auto vertexPath = path.find(vertex);
        if (vertexPath != path.end()) vertexPath->second = NULL;
        else path.insert(pair<Vertex *, Vertex *>(vertex, NULL));

        vertex->setCluster(0);
    }

    clusters.clear();

    MutablePriorityQueue<Vertex> vertexQueue;
    for (Vertex *v : this->starts) {
        dist.at(v) = 0;
        vertexQueue.insert(v);
        v->setCluster(v->getId());
        clusters[v->getId()] = std::set<size_t>();
    }

    while(!vertexQueue.empty()){
        Vertex *v = vertexQueue.extractMin();

        for (Edge * edge : v->getOutgoing()) {
            Vertex * destinationVertex = edge->getDest();

            if (dist.at(destinationVertex) > dist.at(v) + edge->getWeight()) {

                if (v->getSCC() == destinationVertex->getSCC()) {
                    dist.at(destinationVertex) = dist.at(v) + edge->getWeight();
                    path.at(destinationVertex) = v;

                    destinationVertex->setCluster(v->getCluster());
                } else {
                        //TODO see what todo (noice)
                }
                vertexQueue.insertOrDecreaseKey(destinationVertex);
            }
        }
    }

    // TODO optimize this
    for (Vertex * v : vertexSet) {
        if (v->getType() == APPLICATION_CENTER)
            clusters.at(v->getCluster()).insert(v->getId());
    }

}

unordered_map<std::size_t, std::set<size_t>> MultiSourceDijkstra::getClusters() const {
    return this->clusters;
}
