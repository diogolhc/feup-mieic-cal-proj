//
// Created by sense on 12/05/2021.
//

#include "NearestNeighbor.h"

#include "../shortest-path/Dijkstra.h"

#include <algorithm>
#include <iostream>

using namespace std;

void NearestNeighbor::initialize(Graph *graph, int origin_id, const vector<int> &application_center_ids) {
    this->graph = graph;
    this->s = graph->findVertex(origin_id);
    this->application_center_ids = application_center_ids;
}

std::vector<Vertex *> NearestNeighbor::run() {

    Vertex * v = s;

    Dijkstra dijkstra;
    dijkstra.initialize(graph, v->getId());

    while(!application_center_ids.empty()){

        v = dijkstra.getNearestAC();

        v->setACVisited(true);

        auto iter_v = find(application_center_ids.begin(), application_center_ids.end(), v->getId());

        if (iter_v == application_center_ids.end()){
            cerr << "ERROR NearestNeighbor l:36" << endl;
        }

        application_center_ids.erase(iter_v);

        unordered_map<Vertex *, Vertex *> path = dijkstra.getPath();

        int count = 0;

        Vertex * w = v;

        while(count < path.size()){ //Doesn't include current destination
            w = path.at(w);
            this->running_path.insert(this->running_path.begin(), w);
            count++;
        }

        dijkstra.changeOriginId(v->getId());

    }


    return running_path;
}


