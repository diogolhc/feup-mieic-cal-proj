//
// Created by sense on 16/05/2021.
//

#include "ApplicationCenter.h"

ApplicationCenter::ApplicationCenter(Vertex *vertex1) {
    this->vertex = vertex1;
}

Vertex *ApplicationCenter::getVertex() const {
    return vertex;
}



bool SortByLat::operator() (ApplicationCenter * left,  ApplicationCenter * right) const {
    return left->getVertex()->getCoordinates().lat < right->getVertex()->getCoordinates().lat;
}


bool SortByLng::operator() (ApplicationCenter * left,  ApplicationCenter * right) const {
    return left->getVertex()->getCoordinates().lon < right->getVertex()->getCoordinates().lon;
}
