#include <iostream>
#include <chrono>

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

int main() {
    GraphFiles graphFiles(FILES_ROOT);
    /// GraphFile Portugal = graphFiles.getPortugal();
    GraphFile Porto = graphFiles.getPortoStrongComponent();

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
        storageCenter.initTruckAC();
    }

    for (StorageCenter & storageCenter: Porto.getStorageCenters()) {

        std::vector<ApplicationCenter> acc = storageCenter.getAcCluster();

        NearestNeighbor nearestNeighbor;
        nearestNeighbor.initialize(&graph, storageCenter.getVertex()->getId(), &storageCenter.getTrucks().at(0));

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

