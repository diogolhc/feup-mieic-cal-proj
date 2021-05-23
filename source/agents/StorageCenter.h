#ifndef SOURCE_STORAGECENTER_H
#define SOURCE_STORAGECENTER_H

#include "ApplicationCenter.h"
#include "Truck.h"

#include <vector>

class StorageCenter {
    size_t vaccines;
    std::vector<ApplicationCenter> AcCluster;
    std::vector<Truck *> trucks;
    Vertex * vertex;
public:
    explicit StorageCenter(Vertex * vertex, const vector<Truck *> & trucks);
    void addApplicationCenter(const ApplicationCenter & applicationCenter);
    Vertex * getVertex() const;
    std::vector<ApplicationCenter>& getAcCluster();
    std::vector<Truck *> & getTrucks();
    void clearTrucks();
    size_t getVaccines() const;
    void clearApplicationCenters();
    int getAcClusterSize() const;
};


#endif //SOURCE_STORAGECENTER_H
