#include "ApplicationCenter.h"

ApplicationCenter::ApplicationCenter(Vertex *vertex1) {
    this->vertex = vertex1;
    this->vaccinesNeeded = 0;
}

ApplicationCenter::ApplicationCenter(Vertex *vertex1, int vaccines) {
    this->vertex = vertex1;
    this->vaccinesNeeded = vaccines;
}

Vertex *ApplicationCenter::getVertex() const {
    return vertex;
}

int ApplicationCenter::getVaccinesNeeded() const {
    return this->vaccinesNeeded;
}


bool SortByLat::operator() (ApplicationCenter * left,  ApplicationCenter * right) const {
    return left->getVertex()->getCoordinates().lat < right->getVertex()->getCoordinates().lat;
}


bool SortByLng::operator() (ApplicationCenter * left,  ApplicationCenter * right) const {
    return left->getVertex()->getCoordinates().lon < right->getVertex()->getCoordinates().lon;
}
