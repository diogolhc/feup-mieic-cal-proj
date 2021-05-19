#include <iostream>
#include <chrono>

#include <algorithm>
#include "algorithms/travelling-salesman/NearestNeighbor.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "Graph.h"
#include "algorithms/acessibility/BreathFirstSearch.h"
#include "algorithms/acessibility/DepthFirstSearch.h"
#include "algorithms/vehicle-routing/MultiSourceDijkstra.h"
#include "algorithms/shortest-path/AStar.h"

#include "GraphFiles.h"
#include "View/View.h"


#define FILES_ROOT "../maps"

using namespace std;

const bool PASS_LIMIT_TIME = true;

// res is empty
void splitApplicationCentersSameCluster(std::vector<ApplicationCenter *> original, std::vector< vector<ApplicationCenter *> > &res) {
    if (original.empty())
        return;

    res.clear();
    for (size_t i = 0; i < 2; i++)
        res.emplace_back();

    double latMin = 361;
    double latMax = -361;
    double lngMin = 361;
    double lngMax = -361;

    for (const ApplicationCenter *applicationCenter : original) {
        double lat = applicationCenter->getVertex()->getCoordinates().lat;
        double lng = applicationCenter->getVertex()->getCoordinates().lon;
        if (lat > latMax)
            latMax = lat;
        else if (lat < latMin)
            latMin = lat;

        if (lng > lngMax)
            lngMax = lng;
        else if (lng < lngMin)
            lngMin = lng;
    }

    double latDiff = latMax - latMin;
    double lngDiff = lngMax - lngMin;

    if (latDiff > lngDiff) {
        sort(original.begin(), original.end(), SortByLat());

        double latCenter = latMin + latDiff/2;
        size_t i = 0;
        while (i < original.size() && original.at(i)->getVertex()->getCoordinates().lat < latCenter) {
            res.at(0).push_back(original.at(i));
            i++;
        }

        for (; i < original.size(); i ++) {
            res.at(1).push_back(original.at(i));
        }

    } else {
        sort(original.begin(), original.end(), SortByLng());

        double lngCenter = lngMin + lngDiff/2;
        size_t i = 0;
        while (i < original.size() && original.at(i)->getVertex()->getCoordinates().lon < lngCenter) {
            res.at(0).push_back(original.at(i));
            i++;
        }

        for (; i < original.size(); i ++) {
            res.at(1).push_back(original.at(i));
        }

    }
}

void assignGridToTrucks(StorageCenter & storageCenter, std::vector< vector<ApplicationCenter *> > res){

    for (vector<ApplicationCenter*> & v : res){
        if (v.empty()) continue;
        storageCenter.addTruck(v);
    }
}

void recursiveTruckPath(Graph & graph, StorageCenter & storageCenter, int distLim, std::vector<ApplicationCenter *> original){

    vector<Truck> & trucks = storageCenter.getTrucks();

    if (original.size() == 0){
        return;
    }

    trucks.emplace_back(100, original);

    NearestNeighbor nearestNeighbor;
    nearestNeighbor.initialize(&graph, storageCenter.getVertex()->getId(), &trucks.at(trucks.size()-1));

    vector<Vertex *> nnRes = nearestNeighbor.run();


    if (trucks.at(trucks.size()-1).getDistanceCovered() > distLim){

        std::vector< vector<ApplicationCenter *> > res;
        splitApplicationCentersSameCluster(original, res);

        if (original.size() == res.at(0).size() || original.size() == res.at(1).size()){

            if(!PASS_LIMIT_TIME){
                trucks.at(trucks.size()-1).undo();
                trucks.erase(trucks.end()-1);
            }

            return;
        }

        trucks.at(trucks.size()-1).undo();
        trucks.erase(trucks.end()-1);

        recursiveTruckPath(graph, storageCenter, distLim, res.at(0));
        recursiveTruckPath(graph, storageCenter, distLim, res.at(1));
    }


    return;


}


int main() {
    srand(time(0));
    GraphFiles graphFiles(FILES_ROOT);
    /// GraphFile Portugal = graphFiles.getPortugal();
    GraphFile Porto = graphFiles.getPorto();

    Graph graph = Porto.getGraph();

    //A*
    Vertex *source = graph.findVertex(14432);
    Vertex *dest = graph.findVertex(30030);

    AStar aStar(&graph, source, dest);
    aStar.run();
    if (aStar.getPath().empty())
        cout << "No possible path\n";
    cout << "A* vertex count viewed: " << aStar.getVertexViewedCount() << endl; // TODO fazer semelhante ao Dijkstra para dar para comparar tempos de execução e vertices analizados de modo a tirar umas conclusões empiricas para o relatório

    /*
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
        for (size_t id : clusters.at(storageCenter.getVertex()->getId())) {
            for (ApplicationCenter applicationCenter : Porto.getApplicationCenters()) {
                if ( applicationCenter.getVertex()->getId() == id ) {
                    // ApplicationCenter ac(graph.findVertex(id), applicationCenter.getVaccinesNeeded());
                    storageCenter.addApplicationCenter(applicationCenter);
                }
            }
        }
    }

    for (StorageCenter & storageCenter: Porto.getStorageCenters()) {
        std::vector<ApplicationCenter *> original;
        for (ApplicationCenter & applicationCenter : storageCenter.getAcCluster())
            original.push_back(&applicationCenter);

        recursiveTruckPath(graph, storageCenter, 100000, original);
    }

    for (StorageCenter & storageCenter : Porto.getStorageCenters()){
        cout << "Storage: " << storageCenter.getVertex()->getId() << " Vaccines: " << storageCenter.getVaccines() << endl;
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
/*
    size_t idx = 0;
    int max = 0;
    vector<std::size_t > sccMap = kosas.getMap();
    for (int i = 0; i < sccMap.size(); i++) {
        if (sccMap[i] > max) {
            idx = i;
            max = sccMap[i];
        }
    }
*/
    viewState state = SHORTEST_PATH;

    view(Porto, state);

    return 0;
}

