//
// Created by sense on 16/05/2021.
//

#include "StorageCenter.h"

StorageCenter::StorageCenter(Vertex *vertex, const vector<Truck> & trucks) {
    this->vertex = vertex;
    this->trucks = trucks;
}

void StorageCenter::addApplicationCenter(const ApplicationCenter &applicationCenter) {
    this->AcCluster.push_back(applicationCenter);
}

std::vector<ApplicationCenter> &StorageCenter::getAcCluster() { //TODO using the reference so it's faster JAVA style
    return this->AcCluster;
}

Vertex *StorageCenter::getVertex() const{
    return vertex;
}

void StorageCenter::initTruckAC(){

    Truck & truck = this->trucks.at(0);

    for (ApplicationCenter & applicationCenter : this->AcCluster){

        truck.addApplicationCenter(&applicationCenter);

    }

}

std::vector<Truck> &StorageCenter::getTrucks() {
    return trucks;
}

