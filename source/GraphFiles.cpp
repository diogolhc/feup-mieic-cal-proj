#include "GraphFiles.h"
#include "Graph.h"

#include <fstream>
#include <iostream>

using namespace std;


GraphFile::GraphFile(double scale, const Coordinates &centralCoordinates, const std::string &nodes_file_latlng, const std::string &edges_file, const std::string &back_ground_file) :
    nodes_file_latlng(nodes_file_latlng),
    edges_file(edges_file),
    background_file(back_ground_file),
    loaded(false),
    scale(scale),
    centralCoordinates(centralCoordinates)
    {}


Graph GraphFile::getGraph() {
    if (!this->loaded)
        this->load();
    return graph;
}


void GraphFile::load() {
    ifstream node_stream_latlng(nodes_file_latlng);
    ifstream edge_stream(edges_file);

    if (node_stream_latlng.fail() || node_stream_latlng.eof() || node_stream_latlng.bad()){
        cout << "Failed to load node file lat lon" << endl;
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
        double lat, lon;
        node_stream_latlng >> trash >> id >> trash >> lon >> trash >> lat >> trash;
        Vertex *v = graph.addVertex(id);
        v->setCoordinates({.lat = lat, .lon = lon});
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

double GraphFile::getScale() {
    return this->scale;
}

std::string GraphFile::getbackGroundImage() {
    return this->background_file;
}

Coordinates GraphFile::getCentralCoordinates() {
    return this->centralCoordinates;
}

// TODO maybe get this values by a single file latter ?,
// TODO find images and set their respective center here
GraphFiles::GraphFiles(std::string filesDir) :
        Porto(1.0/7000.0, {.lat = 41.146, .lon = -8.6}, filesDir + "/porto_full_nodes_latlng.txt", filesDir + "/porto_full_edges.txt", filesDir + "/porto.jpg"),
        PortoStrongComponent(1.0/7000.0, {.lat = 41.146, .lon = -8.6}, filesDir + "/porto_strong_nodes_latlng.txt", filesDir + "/porto_strong_edges.txt", filesDir + "/porto.jpg"),
        Penafiel(1.0/7000.0, {.lat = 41.202739, .lon = -8.298405}, filesDir + "/penafiel_full_nodes_latlng.txt", filesDir + "/penafiel_full_edges.txt"),
        PenafielStrongComponent(1.0/7000.0, {.lat = 41.202739, .lon = -8.298405},filesDir + "/penafiel_strong_nodes_latlng.txt", filesDir + "/penafiel_strong_edges.txt"),
        Espinho(1.0/7000.0, {.lat = 41.004374, .lon = -8.583490},filesDir + "/espinho_full_nodes_latlng.txt", filesDir + "/espinho_full_edges.txt"),
        EspinhoStrongComponent(1.0/7000.0, {.lat = 41.004374, .lon = -8.583490},filesDir + "/espinho_strong_nodes_latlng.txt", filesDir + "/espinho_strong_edges.txt"),
        Portugal(1.0/1000.0, {.lat = 38.792853, .lon = -9.122247},filesDir + "/nodes_lon_lat_portugal.txt", filesDir + "/edges_portugal.txt")
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

GraphFile GraphFiles::getPorto() {
    Porto.load();
    return Porto;
}

GraphFile GraphFiles::getPortoStrongComponent() {
    PortoStrongComponent.load();
    return PortoStrongComponent;
}

GraphFile GraphFiles::getPenafiel() {
    Penafiel.load();
    return Penafiel;
}

GraphFile GraphFiles::getPenafielStrongComponent() {
    PenafielStrongComponent.load();
    return PenafielStrongComponent;
}

GraphFile GraphFiles::getEspinho() {
    Espinho.load();
    return Espinho;
}

GraphFile GraphFiles::getEspinhoStrongComponent() {
    EspinhoStrongComponent.load();
    return EspinhoStrongComponent;
}

GraphFile GraphFiles::getPortugal() {
    Portugal.load();
    return Portugal;
}
