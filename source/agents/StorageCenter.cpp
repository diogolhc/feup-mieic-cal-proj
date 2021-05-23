#include "StorageCenter.h"

StorageCenter::StorageCenter(Vertex *vertex, const vector<Truck*> & trucks) {
    this->vertex = vertex;
    this->trucks = trucks;
    this->vaccines = 0;
}

void StorageCenter::addApplicationCenter(const ApplicationCenter &applicationCenter) {
    this->AcCluster.push_back(applicationCenter);
    this->vaccines += applicationCenter.getVaccinesNeeded();
}

std::vector<ApplicationCenter> &StorageCenter::getAcCluster() {
    return this->AcCluster;
}

Vertex *StorageCenter::getVertex() const{
    return vertex;
}

std::vector<Truck*> &StorageCenter::getTrucks() {
    return trucks;
}

void StorageCenter::clearTrucks() {

    for (Truck *truck: this->trucks){
        truck->undo();
        delete truck;
    }

    this->trucks.clear();
}

size_t StorageCenter::getVaccines() const {
    return this->vaccines;
}

void StorageCenter::clearApplicationCenters() {
    this->AcCluster.clear();
}

int StorageCenter::getAcClusterSize() const{
    return AcCluster.size();
}

