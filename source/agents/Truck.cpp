//
// Created by sense on 16/05/2021.
//

#include "Truck.h"

#include "../Graph.h"

#include "ApplicationCenter.h"

Truck::Truck(int vaccinesLeft) {
    this->vaccinesLeft = vaccinesLeft;
    this->distanceCovered = 0;
}

std::vector<ApplicationCenter *> &Truck::getACList() {
    return this->ACList;
}

void Truck::addApplicationCenter(ApplicationCenter *applicationCenter) {
    this->ACList.push_back(applicationCenter);
}

void Truck::setDistanceCovered(double distance) {
    this->distanceCovered = distance;
}

double Truck::getDistanceCovered() const{
    return this->distanceCovered;
}

int Truck::getVaccinesLeft() const {
    return this->vaccinesLeft;
}

bool Truck::useVaccines(int numVaccines) {
    if (numVaccines >= this->vaccinesLeft){
        this->vaccinesLeft -= numVaccines;
        return true;
    }
    return false;
}

void Truck::setACList(const std::vector<ApplicationCenter *> & newACList) {
    this->ACList= newACList;
}

Truck::Truck(int vaccinesLeft, const std::vector<ApplicationCenter *> &newACList) {
    this->vaccinesLeft = vaccinesLeft;
    this->distanceCovered = 0;
    this->ACList= newACList;
    this->color = COLOR_VECTOR.at(rand() % COLOR_VECTOR.size());
}

GraphViewer::Color Truck::getColor() const {
    return this->color;
}

void Truck::addEdge(Edge *edge) {
    edgeList.push_back(edge);
}

void Truck::undo() {
    for (Edge * edge : edgeList){
        edge->removeTruck(this);
    }
    edgeList.clear();
    this->distanceCovered = 0;

    for (ApplicationCenter * applicationCenter : ACList){
        Vertex * vertex = applicationCenter->getVertex();
        vertex->setACVisited(false);
        vertex->setVisited(false);
    }

}


