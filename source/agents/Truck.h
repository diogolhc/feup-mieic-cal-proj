//
// Created by sense on 16/05/2021.
//

#ifndef SOURCE_TRUCK_H
#define SOURCE_TRUCK_H

#include <vector>

//#include "ApplicationCenter.h"

class ApplicationCenter;

class Truck {
    double distanceCovered;
    int vaccinesLeft;
    std::vector<ApplicationCenter *> ACList;
public:
    explicit Truck(int vaccinesLeft);
    std::vector<ApplicationCenter *> &getACList();
    void addApplicationCenter(ApplicationCenter * applicationCenter);
    double getDistanceCovered() const;
    void setDistanceCovered(double distance);
    int getVaccinesLeft() const;
    bool useVaccines(int numVaccines);
};


#endif //SOURCE_TRUCK_H
