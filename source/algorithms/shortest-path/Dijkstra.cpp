#include "Dijkstra.h"

#include "../../MutablePriorityQueue.h"
#include "../../agents/ApplicationCenter.h"

#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

void Dijkstra::initialize(Graph *graph, int origin_id) {
    this->graph = graph;
    this->s = graph->findVertex(origin_id);
}

void Dijkstra::run() {

    VertexSet vertexSet = graph->getVertexSet();

    for (Vertex* vertex : vertexSet){

        auto vertexDist = dist.find(vertex);
        if (vertexDist != dist.end()) vertexDist->second = INF;
        else dist.insert(pair<Vertex *, double>(vertex, INF));

        vertex->setDist(INF);

        vertex->setVisited(false);

        vertex->setQueueIndex(0);

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

            if (dist.at(destinationVertex) > dist.at(v) + edge->getWeight()){
                dist.at(destinationVertex) = dist.at(v) + edge->getWeight();
                path.at(destinationVertex) = v;

                destinationVertex->setDist(dist.at(destinationVertex));

                vertexQueue.insertOrDecreaseKey(destinationVertex);
            }
        }
    }
}

unordered_map<Vertex *, Vertex *> Dijkstra::getPath() const {
    return this->path;
}

void Dijkstra::changeOriginId(int origin_id) {
    this->s = graph->findVertex(origin_id);
}


Vertex *Dijkstra::getNearestAC(Truck * truck) {

    VertexSet vertexSet = graph->getVertexSet();

    vector<ApplicationCenter *> aclist = truck->getACList();

    for (Vertex* vertex : vertexSet){

        auto vertexDist = dist.find(vertex);
        if (vertexDist != dist.end()) vertexDist->second = INF;
        else dist.insert(pair<Vertex *, double>(vertex, INF));

        vertex->setDist(INF);

        vertex->setVisited(false);

        vertex->setQueueIndex(0);

        auto vertexPath = path.find(vertex);
        if (vertexPath != path.end()) vertexPath->second = NULL;
        else path.insert(pair<Vertex *, Vertex *>(vertex, NULL));

        vertex->setQueueIndex(0);

    }

    Vertex * v = s;

    dist.at(v) = 0;
    v->setDist(0);

    MutablePriorityQueue<Vertex> vertexQueue;
    vertexQueue.insert(v);

    cout << "E vai uma" << endl;

    while(!vertexQueue.empty()) {

        v = vertexQueue.extractMin();

        if (v->getIsApplicationCenter() && !v->getACVisited() && v->getCluster() == s->getCluster()){

            bool found = false;

            for (ApplicationCenter *applicationCenter : aclist){
                Vertex * vertex = applicationCenter->getVertex();
                if (vertex->getId() == v->getId()){
                    cout << "saiu aqui" << endl;
                    found  = true;
                    break;
                }
            }

            if (found) break;
        }

        for (Edge * edge : v->getOutgoing()){

            Vertex * destinationVertex = edge->getDest();

            if (dist.at(destinationVertex) > dist.at(v) + edge->getWeight()){
                dist.at(destinationVertex) = dist.at(v) + edge->getWeight();
                path.at(destinationVertex) = v;

                destinationVertex->setDist(dist.at(destinationVertex));

                vertexQueue.insertOrDecreaseKey(destinationVertex);
            }
        }
    }

    cout << "Ja acabou jessica " << (v->getType() == APPLICATION_CENTER) << endl;

    return v;
}
