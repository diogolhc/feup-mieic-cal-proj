#include <iostream>
#include "MultiDepotVehicleRouting.h"

#include "algorithms/travelling-salesman/NearestNeighbor.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "algorithms/vehicle-routing/MultiSourceDijkstra.h"

// res is cleared
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
        if (lat < latMin)
            latMin = lat;

        if (lng > lngMax)
            lngMax = lng;
        if (lng < lngMin)
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


void recursiveTruckPath(Graph *graph, StorageCenter * storageCenter, double distLim, bool passLimitTime, const std::vector<ApplicationCenter *> &original){

    vector<Truck*> & trucks = storageCenter->getTrucks();

    if (original.empty()){
        return;
    }

    trucks.push_back(new Truck(100, original));

    NearestNeighbor nearestNeighbor;
    nearestNeighbor.initialize(graph, storageCenter->getVertex()->getId(), trucks.at(trucks.size()-1));

    vector<Vertex *> nnRes = nearestNeighbor.run();


    if (trucks.at(trucks.size()-1)->getDistanceCovered() > distLim){
        if (original.size() == 1) {
            if(!passLimitTime){
                trucks.at(trucks.size()-1)->undo();
                trucks.erase(trucks.end()-1);
            }

            return;
        }

        std::vector< vector<ApplicationCenter *> > res;
        splitApplicationCentersSameCluster(original, res);

        trucks.at(trucks.size()-1)->undo();
        trucks.erase(trucks.end()-1);

        recursiveTruckPath(graph, storageCenter, distLim, passLimitTime, res.at(0));
        recursiveTruckPath(graph, storageCenter, distLim, passLimitTime, res.at(1));
    }

}


void multiDepotVehicleRouting(GraphFile *graphFile, double timeLim, bool passLimitTime) {
    Graph *graph = graphFile->getGraph();

    Kosaraju kosaraju;
    kosaraju.run(graph);

    vector<Vertex *> starts;
    for (const StorageCenter & storageCenter: graphFile->getStorageCenters()) {
        starts.push_back(storageCenter.getVertex());
    }

    MultiSourceDijkstra multiSourceDijkstra(graph, starts);

    multiSourceDijkstra.run();

    unordered_map<std::size_t, std::set<size_t>> clusters = multiSourceDijkstra.getClusters();

    for (StorageCenter & storageCenter: graphFile->getStorageCenters()) { //TODO Maybe eliminate intermediate step
        for (size_t id : clusters.at(storageCenter.getVertex()->getId())) {
            for (ApplicationCenter applicationCenter : graphFile->getApplicationCenters()) {
                if ( applicationCenter.getVertex()->getId() == id ) {
                    storageCenter.addApplicationCenter(applicationCenter);
                    break;
                }
            }
        }
    }

    for (StorageCenter & storageCenter: graphFile->getStorageCenters()) {
        std::vector<ApplicationCenter *> original;
        for (ApplicationCenter & applicationCenter : storageCenter.getAcCluster())
            original.push_back(&applicationCenter);

        recursiveTruckPath(graph, &storageCenter, timeLim, passLimitTime, original);
    }

    // TODO this should be done outside in the outer class
    for (StorageCenter & storageCenter : graphFile->getStorageCenters()){
        cout << "Storage: " << storageCenter.getVertex()->getId() << " Vaccines: " << storageCenter.getVaccines() << " Number of application centers: " << storageCenter.getAcClusterSize() << endl;
        for (Truck * truck : storageCenter.getTrucks()){
            cout << "Truck from " << storageCenter.getVertex()->getId() << " covered : " << truck->getDistanceCovered() << endl;
        }
    }

}
