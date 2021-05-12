#ifndef SOURCE_GRAPHFILES_H
#define SOURCE_GRAPHFILES_H

#include <string>
#include "Graph.h"

class GraphFile {
private:
    std::string nodes_file_latlng; // (id, lat, lon)
    std::string edges_file; // (id1, id2)
    std::string background_file;
    Graph graph;
    bool loaded;
    double scale;
    Coordinates centralCoordinates;
public:
    GraphFile(double scale, const Coordinates &centralCoordinates, const std::string &nodes_file_lat_lng, const std::string &edges_file, const std::string &back_ground_file="");
    void load();
    Graph getGraph();
    double getScale();
    std::string getbackGroundImage();
    Coordinates getCentralCoordinates();
};


class GraphFiles {
private:
    GraphFile Porto;
    GraphFile PortoStrongComponent;

    GraphFile Penafiel;
    GraphFile PenafielStrongComponent;

    GraphFile Espinho;
    GraphFile EspinhoStrongComponent;

    GraphFile Portugal;

public:
    GraphFiles(std::string filesDir);
    void load();

    // getters will load the respective graph if not loaded before
    GraphFile getPorto();
    GraphFile getPortoStrongComponent();
    GraphFile getPenafiel();
    GraphFile getPenafielStrongComponent();
    GraphFile getEspinho();
    GraphFile getEspinhoStrongComponent();
    GraphFile getPortugal();

};


#endif //SOURCE_GRAPHFILES_H
