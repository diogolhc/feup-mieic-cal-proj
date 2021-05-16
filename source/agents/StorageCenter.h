//
// Created by sense on 16/05/2021.
//

#ifndef SOURCE_STORAGECENTER_H
#define SOURCE_STORAGECENTER_H

#include "../Graph.h"
#include "ApplicationCenter.h"
#include "Truck.h"

#include <vector>

class StorageCenter {
    std::vector<ApplicationCenter> AcCluster;
    std::vector<Truck> trucks;
    Vertex * vertex;
public:
    explicit StorageCenter(Vertex * vertex);
    void addApplicationCenter(const ApplicationCenter & applicationCenter);
    Vertex * getVertex() const;
    std::vector<ApplicationCenter>& getAcCluster();
};


#endif //SOURCE_STORAGECENTER_H
