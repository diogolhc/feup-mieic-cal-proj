//
// Created by sense on 16/05/2021.
//

#include "ApplicationCenter.h"

ApplicationCenter::ApplicationCenter(Vertex *vertex) {
    this->vertex = vertex;
}

Vertex *ApplicationCenter::getVertex() const {
    return vertex;
}
