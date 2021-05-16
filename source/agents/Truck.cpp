//
// Created by sense on 16/05/2021.
//

#include "Truck.h"

Truck::Truck(int vaccinesLeft) {
    this->vaccinesLeft = vaccinesLeft;
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


