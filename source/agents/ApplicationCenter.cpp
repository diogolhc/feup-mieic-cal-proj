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
