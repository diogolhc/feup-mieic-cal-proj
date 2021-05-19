//
// Created by sense on 16/05/2021.
//

#include "StorageCenter.h"

StorageCenter::StorageCenter(Vertex *vertex, const vector<Truck> & trucks) {
    this->vertex = vertex;
    this->trucks = trucks;
    this->vaccines = 0;
}

void StorageCenter::addApplicationCenter(const ApplicationCenter &applicationCenter) {
    this->AcCluster.push_back(applicationCenter);
    this->vaccines += applicationCenter.getVaccinesNeeded();
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

void StorageCenter::addTruck(const std::vector<ApplicationCenter *> & newACList) {
    this->trucks.emplace_back(0, newACList);
}

void StorageCenter::clearTrucks() {

    for (Truck &truck: this->trucks){
        truck.undo();
    }

    this->trucks.clear();
}

size_t StorageCenter::getVaccines() const {
    return this->vaccines;
}

