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
    GraphFile Porto = graphFiles.getPorto();

    Graph graph = Porto.getGraph();

    Kosaraju kosas;
    kosas.run(graph);

    vector<Vertex *> starts;
    for (size_t id: Porto.getStorage_centers_ids()) {
        starts.push_back(graph.findVertex(id));
    }

    MultiSourceDijkstra multiSourceDijkstra(&graph, starts);
    multiSourceDijkstra.run();

    unordered_map<std::size_t, std::set<size_t>> clusters = multiSourceDijkstra.getClusters();

    for (pair<size_t, std::set<size_t>> cluster: clusters) {
        cout << cluster.first << endl;
        for (size_t id : cluster.second) {
            cout << id << " ";
        }
        cout << "\n";
    }


    for (pair<size_t, std::set<size_t>> cluster: clusters) {
        vector<size_t> clustersV;
        std::copy(cluster.second.begin(), cluster.second.end(), std::back_inserter(clustersV));

        NearestNeighbor nearestNeighbor;
        nearestNeighbor.initialize(&graph, cluster.first, clustersV);

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

