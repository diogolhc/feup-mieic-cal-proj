#ifndef SOURCE_GRAPHFILES_H
#define SOURCE_GRAPHFILES_H

#include <string>

#include "agents/StorageCenter.h"
#include "Graph.h"

class GraphFile {
private:
    std::string nodes_file_latlng; // (id, lat, lon)
    std::string edges_file; // (id1, id2)
    std::string background_file;
    std::string centers_file;
    Graph graph;
    bool loaded;
    double scale;
    Coordinates centralCoordinates;
    vector<size_t> application_centers_ids;
    vector<size_t> storage_centers_ids;
    vector<StorageCenter> storageCenters;
    vector<ApplicationCenter> applicationCenters;

public:
    GraphFile(double scale, const Coordinates &centralCoordinates, const std::string &nodes_file_lat_lng, const std::string &edges_file, const std::string &back_ground_file="", const std::string &centers_file="");
    void load();
    Graph* getGraph();
    double getScale();
    std::string getBackGroundImage() const;
    Coordinates getCentralCoordinates() const;
    vector<StorageCenter> & getStorageCenters();
    vector<ApplicationCenter> getApplicationCenters();
    GraphFile* getGraphFile();
    void reset();
};


class GraphFiles {
private:
    GraphFile Porto;
    GraphFile PortoStrongComponent;

    GraphFile Penafiel;
    GraphFile PenafielStrongComponent;

    GraphFile Espinho;
    GraphFile EspinhoStrongComponent;

public:
    GraphFiles(const std::string &filesDir);
    void load();

    // getters will load the respective graph if not loaded before
    GraphFile* getPorto();
    GraphFile* getPortoStrongComponent();
    GraphFile* getPenafiel();
    GraphFile* getPenafielStrongComponent();
    GraphFile* getEspinho();
    GraphFile* getEspinhoStrongComponent();
};


#endif //SOURCE_GRAPHFILES_H
