#ifndef SOURCE_GRAPHFILES_H
#define SOURCE_GRAPHFILES_H

#include <string>
#include "Graph.h"

class GraphFile {
private:
    std::string nodes_file_latlng; // (id, lat, lng)
    std::string edges_file; // (id1, id2)
    Graph graph;
    bool loaded;
public:
    GraphFile(const std::string &nodes_file_lat_lng, const std::string &edges_file);
    void load();
    Graph getGraph();
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
    Graph getPorto();
    Graph getPortoStrongComponent();
    Graph getPenafiel();
    Graph getPenafielStrongComponent();
    Graph getEspinho();
    Graph getEspinhoStrongComponent();
    Graph getPortugal();

};


#endif //SOURCE_GRAPHFILES_H
