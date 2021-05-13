//
// Created by sense on 12/05/2021.
//

#include "Dijkstra.h"

#include "../../MutablePriorityQueue.h"

#include <unordered_set>

void Dijkstra::initialize(Graph *graph, int origin_id) {
    this->graph = graph;
    this->s = graph->findVertex(origin_id);
}

void Dijkstra::run() {

    VertexSet vertexSet = graph->getVertexSet();

    for (Vertex* vertex : vertexSet){

        auto vertexDist = dist.find(vertex);
        if (vertexDist != dist.end()) vertexDist->second = INF;
        else dist.insert(pair<Vertex *, std::size_t>(vertex, INF));

        auto vertexPath = path.find(vertex);
        if (vertexPath != path.end()) vertexPath->second = NULL;
        else path.insert(pair<Vertex *, Vertex *>(vertex, NULL));
    }

    Vertex * v = s;

    dist.at(v) = 0;

    MutablePriorityQueue<Vertex> vertexQueue;
    vertexQueue.insert(v);

    while(!vertexQueue.empty()){

        v = vertexQueue.extractMin();

        for (Edge * edge : v->getOutgoing()){

            Vertex * destinationVertex = edge->getDest();

            size_t oldDist = dist.at(destinationVertex);

            if (dist.at(destinationVertex) > dist.at(v) + edge->getWeight()){
                dist.at(destinationVertex) = dist.at(v) + edge->getWeight();
                path.at(destinationVertex) = v;

                if (oldDist == INF){
                    vertexQueue.insert(destinationVertex);
                }
                else{
                    vertexQueue.decreaseKey(destinationVertex);
                }
            }
        }
    }
}

unordered_map<Vertex *, Vertex *> Dijkstra::getPath() const {
    return this->path;
}
