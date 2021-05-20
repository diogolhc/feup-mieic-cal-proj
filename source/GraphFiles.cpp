#include "GraphFiles.h"
#include "Graph.h"

#include <fstream>
#include <iostream>

using namespace std;


GraphFile::GraphFile(double scale, const Coordinates &centralCoordinates, const std::string &nodes_file_latlng, const std::string &edges_file, const std::string &back_ground_file, const std::string &centers_file) :
    nodes_file_latlng(nodes_file_latlng),
    edges_file(edges_file),
    background_file(back_ground_file),
    loaded(false),
    scale(scale),
    centralCoordinates(centralCoordinates),
    centers_file(centers_file)
    {}


Graph* GraphFile::getGraph() {
    if (!this->loaded)
        this->load();
    return &graph;
}


void GraphFile::load() {
    ifstream node_stream_latlng(nodes_file_latlng);
    ifstream edge_stream(edges_file);
    ifstream centers_stream(centers_file);

    if (node_stream_latlng.fail() || node_stream_latlng.eof() || node_stream_latlng.bad()){
        cout << "Failed to load node file lat lon" << endl;
        exit(1);
    }

    if (edge_stream.fail() || edge_stream.eof() || edge_stream.bad()){
        cout << "Failed to load edge file" << endl;
        exit(1);
    }

    if (centers_stream.fail() || centers_stream.eof() || centers_stream.bad()){
        cout << "Failed to load centers file" << endl;
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
        v->setType(NONE);
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


    size_t id;
    int vaccines;
    centers_stream >> size;
    for (int i = 0; i < size; i++) {
        centers_stream >> id;
        Vertex *v = graph.findVertex(id);
        v->setType(STORAGE_CENTER);
        this->storage_centers_ids.push_back(id);
        this->storageCenters.emplace_back(v, vector<Truck*>()); //TODO change this
    }

    centers_stream >> size;
    for (int i = 0; i < size; i++) {
        centers_stream >> id >> vaccines;
        Vertex *v = graph.findVertex(id);
        v->setType(APPLICATION_CENTER);
        this->application_centers_ids.push_back(id);
        ApplicationCenter ac(v, vaccines);
        this->applicationCenters.emplace_back(ac);
    }

    centers_stream.close();
    this->loaded = true;
}

double GraphFile::getScale() {
    return this->scale;
}

std::string GraphFile::getbackGroundImage() const {
    return this->background_file;
}

Coordinates GraphFile::getCentralCoordinates() const {
    return this->centralCoordinates;
}

vector<size_t> GraphFile::getApplication_centers_ids() const {
    return this->application_centers_ids;
}

vector<size_t> GraphFile::getStorage_centers_ids() const {
    return this->storage_centers_ids;
}

vector<StorageCenter> &GraphFile::getStorageCenters() {
    return this->storageCenters;
}

vector<ApplicationCenter> GraphFile::getApplicationCenters() {
    return this->applicationCenters;
}

// TODO maybe get this values by a single file latter ?,
// TODO find images and set their respective center here
GraphFiles::GraphFiles(const std::string &filesDir) :
        Porto(1.0/7000.0, {.lat = 41.146, .lon = -8.6}, filesDir + "/porto_full_nodes_latlng.txt", filesDir + "/porto_full_edges.txt", filesDir + "/porto.jpg", filesDir + "/porto_centers.txt"),
        PortoStrongComponent(1.0/7000.0, {.lat = 41.146, .lon = -8.6}, filesDir + "/porto_strong_nodes_latlng.txt", filesDir + "/porto_strong_edges.txt", filesDir + "/porto.jpg", filesDir + "/porto_strong_centers.txt"),
        Penafiel(1.0/7000.0, {.lat = 41.202739, .lon = -8.298405}, filesDir + "/penafiel_full_nodes_latlng.txt", filesDir + "/penafiel_full_edges.txt", "", filesDir + "/penafiel_centers.txt"),
        PenafielStrongComponent(1.0/7000.0, {.lat = 41.202739, .lon = -8.298405},filesDir + "/penafiel_strong_nodes_latlng.txt", filesDir + "/penafiel_strong_edges.txt", "", filesDir + "/penafiel_strong_centers.txt"),
        Espinho(1.0/7000.0, {.lat = 41.004374, .lon = -8.583490},filesDir + "/espinho_full_nodes_latlng.txt", filesDir + "/espinho_full_edges.txt"),
        EspinhoStrongComponent(1.0/7000.0, {.lat = 41.004374, .lon = -8.583490},filesDir + "/espinho_strong_nodes_latlng.txt", filesDir + "/espinho_strong_edges.txt"),
        Portugal(1.0/1000.0, {.lat = 38.792853, .lon = -9.122247},filesDir + "/nodes_lon_lat_portugal.txt", filesDir + "/edges_portugal.txt")
        {}
/*
void GraphFiles::load() {
    Porto.load();
    PortoStrongComponent.load();
    Penafiel.load();
    PenafielStrongComponent.load();
    Espinho.load();
    EspinhoStrongComponent.load();
    Portugal.load();
}
*/
GraphFile* GraphFiles::getPorto() {
    Porto.load();
    return &Porto;
}

GraphFile* GraphFiles::getPortoStrongComponent() {
    PortoStrongComponent.load();
    return &PortoStrongComponent;
}

GraphFile* GraphFiles::getPenafiel() {
    Penafiel.load();
    return &Penafiel;
}

GraphFile* GraphFiles::getPenafielStrongComponent() {
    PenafielStrongComponent.load();
    return &PenafielStrongComponent;
}

GraphFile* GraphFiles::getEspinho() {
    Espinho.load();
    return &Espinho;
}

GraphFile* GraphFiles::getEspinhoStrongComponent() {
    EspinhoStrongComponent.load();
    return &EspinhoStrongComponent;
}

GraphFile* GraphFiles::getPortugal() {
    Portugal.load();
    return &Portugal;
}
