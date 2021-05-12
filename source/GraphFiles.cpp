#include "GraphFiles.h"

#include <fstream>
#include <iostream>

using namespace std;


GraphFile::GraphFile(const std::string &nodes_file_latlng, const std::string &edges_file) : nodes_file_latlng(nodes_file_latlng), edges_file(edges_file), loaded(false) {}


Graph GraphFile::getGraph() {
    if (!this->loaded)
        this->load();
    return graph;
}


void GraphFile::load() {
    ifstream node_stream_latlng(nodes_file_latlng);
    ifstream edge_stream(edges_file);

    if (node_stream_latlng.fail() || node_stream_latlng.eof() || node_stream_latlng.bad()){
        cout << "Failed to load node file lat lng" << endl;
        exit(1);
    }

    if (edge_stream.fail() || edge_stream.eof() || edge_stream.bad()){
        cout << "Failed to load edge file" << endl;
        exit(1);
    }

    int size;
    char trash;

    node_stream_latlng >> size;

    for (int i = 0; i < size; i++){
        size_t id;
        double lat, lng;
        node_stream_latlng >> trash >> id >> trash >> lat >> trash >> lng >> trash;
        Vertex *v = graph.addVertex(id);
        v->setCoordinates({.lat = lat, .lng = lng});
    }
    node_stream_latlng.close();

    edge_stream >> size;
    for (int i = 0; i < size; i++){
        size_t id1, id2;
        edge_stream >> trash >> id1 >> trash >> id2 >> trash;
        Vertex *v1 =  graph.findVertex(id1);
        Vertex *v2 =  graph.findVertex(id2);
        if (v1 == nullptr || v2 == nullptr) {
            cerr << "Node ids of edge not found: " << id1 << " " << id2 << endl;
            exit(1);
        }
        double distance = v1->getCoordinates().dist(v2->getCoordinates());
        graph.addEdge(v1, v2, distance);
    }

    edge_stream.close();
    this->loaded = true;
}


GraphFiles::GraphFiles(std::string filesDir) :
        Porto(filesDir + "/porto_full_nodes_latlng.txt", filesDir + "/porto_full_edges.txt"),
        PortoStrongComponent(filesDir + "/porto_strong_nodes_latlng.txt", filesDir + "/porto_strong_edges.txt"),
        Penafiel(filesDir + "/penafiel_full_nodes_latlng.txt", filesDir + "/penafiel_full_edges.txt"),
        PenafielStrongComponent(filesDir + "/penafiel_strong_nodes_latlng.txt", filesDir + "/penafiel_strong_edges.txt"),
        Espinho(filesDir + "/espinho_full_nodes_latlng.txt", filesDir + "/espinho_full_edges.txt"),
        EspinhoStrongComponent(filesDir + "/espinho_strong_nodes_latlng.txt", filesDir + "/espinho_strong_edges.txt"),
        Portugal(filesDir + "/nodes_lat_lon_portugal.txt", filesDir + "/edges_portugal.txt")
        {}

void GraphFiles::load() {
    Porto.load();
    PortoStrongComponent.load();
    Penafiel.load();
    PenafielStrongComponent.load();
    Espinho.load();
    EspinhoStrongComponent.load();
    Portugal.load();
}

Graph GraphFiles::getPorto() {
    return Porto.getGraph();
}

Graph GraphFiles::getPortoStrongComponent() {
    return PortoStrongComponent.getGraph();
}

Graph GraphFiles::getPenafiel() {
    return Penafiel.getGraph();
}

Graph GraphFiles::getPenafielStrongComponent() {
    return PenafielStrongComponent.getGraph();
}

Graph GraphFiles::getEspinho() {
    return Espinho.getGraph();
}

Graph GraphFiles::getEspinhoStrongComponent() {
    return EspinhoStrongComponent.getGraph();
}

Graph GraphFiles::getPortugal() {
    return Portugal.getGraph();
}
