#ifndef SOURCE_GRAPHLOADER_H
#define SOURCE_GRAPHLOADER_H

#include <list>
#include <tuple>
#include <fstream>

#include "Graph.h"


void graphLoader(const std::string &node_file_latlng, const std::string &node_file_xy, const std::string &edge_file, Graph &graph) {
    ifstream node_stream_latlng(node_file_latlng);
    ifstream node_stream_xy(node_file_xy);
    ifstream edge_stream(edge_file);

    if (node_stream_latlng.fail() || node_stream_latlng.eof() || node_stream_latlng.bad()){
        cout << "Failed to load node file lat lng" << endl;
        exit(1);
    }

    if (node_stream_xy.fail() || node_stream_xy.eof() || node_stream_xy.bad()){
        cout << "Failed to load node file x y" << endl;
        exit(1);
    }

    if (edge_stream.fail() || edge_stream.eof() || edge_stream.bad()){
        cout << "Failed to load edge file" << endl;
        exit(1);
    }

    int size;
    char trash;

    node_stream_latlng >> size;
    node_stream_xy >> size; // same, just to take it out

    for (int i = 0; i < size; i++){
        size_t id;
        double lat, lng;
        double x, y;
        node_stream_latlng >> trash >> id >> trash >> lat >> trash >> lng >> trash;
        node_stream_xy >> trash >> trash >> trash >> x >> trash >> y >> trash;
        Vertex *v = graph.addVertex(id);
        v->setCoordinates({.lat = lat, .lng = lng});
        v->setXY({.x = x, .y = y});
    }
    node_stream_latlng.close();
    node_stream_xy.close();

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
}


#endif //SOURCE_GRAPHLOADER_H
