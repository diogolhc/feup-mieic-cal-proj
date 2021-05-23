#include "NearestNeighbor.h"

#include "../shortest-path/Dijkstra.h"

#include <algorithm>
#include <iostream>

using namespace std;

void NearestNeighbor::initialize(Graph *graph, size_t origin_id, Truck * truck) {
    this->graph = graph;
    this->s = graph->findVertex(origin_id);
    this->truck = truck;
}

std::vector<Vertex *> NearestNeighbor::run() {

    Vertex * v = s;

    Dijkstra dijkstra;
    dijkstra.initialize(graph, v->getId());

    int count1 = 0;

    vector<ApplicationCenter *> aclist = truck->getACList();

    cout << "NN for " << this->s->getId() << " : ";

    while(count1 < aclist.size()){

        Vertex * s1 = v;

        v = dijkstra.getNearestAC(truck);

        v->setACVisited(true);

        count1++;

        unordered_map<Vertex *, Vertex *> path = dijkstra.getPath();

        int count = 0;

        Vertex * w = v;

        int start = this->running_path.size();

        while(w != s1){ //Doesn't include current destination
            w = path.at(w);
            this->running_path.insert(this->running_path.begin() + start, w);
            count++;
        }

        dijkstra.changeOriginId(v->getId());

    }

    cout << endl;

    this->running_path.push_back(v);

    std::vector<Vertex *> & res = running_path;

    for (int i = 0; i < res.size() - 1; i++) {

        Vertex *v1 = res.at(i);
        Vertex *v2 = res.at(i + 1);

        for (Edge *edge : v1->getOutgoing()) {
            if (edge->getDest() == v2) {
                edge->passTruck(truck);
                truck->setDistanceCovered(truck->getDistanceCovered() + edge->getWeight());
                break;
            }
        }
    }


    return running_path;
}
