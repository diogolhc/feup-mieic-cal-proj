//
// Created by sense on 16/05/2021.
//

#include "StorageCenter.h"

StorageCenter::StorageCenter(Vertex *vertex) {
    this->vertex = vertex;
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


