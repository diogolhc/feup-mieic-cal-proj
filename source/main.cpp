#include <iostream>
#include <chrono>

#include <algorithm>
#include "algorithms/travelling-salesman/NearestNeighbor.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "Graph.h"
#include "algorithms/acessibility/BreathFirstSearch.h"
#include "algorithms/acessibility/DepthFirstSearch.h"
#include "algorithms/vehicle-routing/MultiSourceDijkstra.h"

#include "GraphFiles.h"
#include "View/View.h"


#define FILES_ROOT "../maps"

using namespace std;

// res is empty
void splitApplicationCentersSameCluster(std::vector<ApplicationCenter *> original, std::vector< vector<ApplicationCenter *> > &res) {
    if (original.size() == 0)
        return;

    res.clear();
    for (size_t i = 0; i < 4; i++)
        res.emplace_back();

    sort(original.begin(), original.end(), SortByLat());

    double latLeft = original.at(0)->getVertex()->getCoordinates().lat;
    double latRight = original.at(original.size() - 1)->getVertex()->getCoordinates().lat;
    double latCenter = latLeft + (latRight - latLeft)/2;


    size_t i = 0;
    while (original.at(i)->getVertex()->getCoordinates().lat < latCenter) {
        res.at(0).push_back(original.at(i));
        i++;
    }

    while (i < original.size()) {
        res.at(1).push_back(original.at(i));
        i++;
    }

    sort(res.at(0).begin(), res.at(0).end(), SortByLng());
    sort(res.at(1).begin(), res.at(1).end(), SortByLng());

    double lngLeft0 = res.at(0).at(0)->getVertex()->getCoordinates().lon;
    double lngLeft1 = res.at(1).at(0)->getVertex()->getCoordinates().lon;
    double lngRight0 = res.at(0).at(res.at(0).size()-1)->getVertex()->getCoordinates().lon;
    double lngRight1 = res.at(1).at(res.at(1).size()-1)->getVertex()->getCoordinates().lon;

    double lngCenter0 = lngLeft0 + (lngRight0 - lngLeft0)/2;
    double lngCenter1 = lngLeft1 + (lngRight1 - lngLeft1)/2;

    i = 0;
    while (res.at(0).at(i)->getVertex()->getCoordinates().lon < lngCenter0) {
        res.at(2).push_back(res.at(0).at(i));
        i++;
    }

    res.at(0).erase(res.at(0).begin(), res.at(0).begin() + i);

    i = 0;
    while (res.at(1).at(i)->getVertex()->getCoordinates().lon < lngCenter1) {
        res.at(3).push_back(res.at(1).at(i));
        i++;
    }

    res.at(1).erase(res.at(1).begin(), res.at(1).begin() + i);
}

void assignGridToTrucks(StorageCenter & storageCenter, std::vector< vector<ApplicationCenter *> > res){

    for (vector<ApplicationCenter*> & v : res){
        if (v.empty()) continue;
        storageCenter.addTruck(v);
    }
}


int main() {
    srand(time(0));
    GraphFiles graphFiles(FILES_ROOT);
    /// GraphFile Portugal = graphFiles.getPortugal();
    GraphFile Porto = graphFiles.getPenafiel();

    Graph graph = Porto.getGraph();

    Kosaraju kosas;
    kosas.run(graph);

    vector<Vertex *> starts;
    for (const StorageCenter & storageCenter: Porto.getStorageCenters()) {
        starts.push_back(storageCenter.getVertex());
    }


    MultiSourceDijkstra multiSourceDijkstra(&graph, starts);

    multiSourceDijkstra.run();

    unordered_map<std::size_t, std::set<size_t>> clusters = multiSourceDijkstra.getClusters();


    for (StorageCenter & storageCenter: Porto.getStorageCenters()) { //TODO Maybe eliminate intermediate step
        for(size_t id : clusters.at(storageCenter.getVertex()->getId())){
            ApplicationCenter applicationCenter(graph.findVertex(id));
            storageCenter.addApplicationCenter(applicationCenter);
        }
    }

    for (StorageCenter & storageCenter: Porto.getStorageCenters()) {
        std::vector<ApplicationCenter *> original;
        for (ApplicationCenter & applicationCenter : storageCenter.getAcCluster())
            original.push_back(&applicationCenter);

        if (original.empty()) {
            storageCenter.getVertex()->setType(NOT_USED_SC);
        } else {
            std::vector< vector<ApplicationCenter *> > res;
            splitApplicationCentersSameCluster(original, res);
            assignGridToTrucks(storageCenter, res);
        }
    }

    for (StorageCenter & storageCenter: Porto.getStorageCenters()) {

        for (Truck & truck : storageCenter.getTrucks()){
            std::vector<ApplicationCenter> acc = storageCenter.getAcCluster();

            NearestNeighbor nearestNeighbor;
            nearestNeighbor.initialize(&graph, storageCenter.getVertex()->getId(), &truck);
            vector<Vertex *> res = nearestNeighbor.run();

            int count = 0;

            for (int i = 0; i < res.size() - 1; i++) {

                Vertex *v1 = res.at(i);
                Vertex *v2 = res.at(i + 1);

                for (Edge *edge : v1->getOutgoing()) {
                    if (edge->getDest() == v2) {
                        count++;
                        edge->setPassedVehicle(true);
                        break;
                    }
                }
            }
        }
    }


    for (StorageCenter & storageCenter : Porto.getStorageCenters()){
        for (Truck & truck : storageCenter.getTrucks()){
            cout << "Truck from " << storageCenter.getVertex()->getId() << " covered : " << truck.getDistanceCovered() << endl;
        }
    }

/*
    Kosaraju kosaraju;
    BreathFirstSearch bfs;
    DepthFirstSearch dfs;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    dfs.run(graph);

    auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as a double.
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms";
*/
    /*
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    kosaraju.run(g);
    auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as a double.
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_double.count() << "ms";
     */

    view(Porto);

    return 0;
}

