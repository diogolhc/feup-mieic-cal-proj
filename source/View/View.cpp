#include <iostream>
#include "View.h"
#include "graphviewer.h"
#include "../Graph.h"
#include "../GraphFiles.h"


// TODO adapt as needed (eg. colors)
void view(GraphFile &graphFile) {
    Graph graph = graphFile.getGraph();
    Coordinates centralCoord = graphFile.getCentralCoordinates();
    GraphViewer gv;
    gv.setScale(graphFile.getScale());
    gv.setCenter(sf::Vector2f(centralCoord.lon, -centralCoord.lat));

    GraphViewer::id_t idNode;
    double lat, lon;
    for (Vertex *v : graph.getVertexSet()) {
        idNode = v->getId();
        lat = v->getCoordinates().lat;
        lon = v->getCoordinates().lon;
        GraphViewer::Node &node = gv.addNode(idNode, sf::Vector2f(lon, -lat));
        node.setOutlineThickness(0.0);
        node.setSize(0.001);

        switch (v->getType()) {
            case NONE:
                node.setSize(0.0); // TODO not print
                break;
            case STORAGE_CENTER:
                node.setColor(GraphViewer::LIGHT_GRAY);
                break;
            case APPLICATION_CENTER:
                node.setColor(GraphViewer::DARK_GRAY);
                break;
        }

    }

    GraphViewer::id_t idEdge = 0, u, v;
    for (Edge *e : graph.getEdges()) {
        // WARNING this is switched due to a bug in the graphViewer version used (it displays arrows from destination node to origin node)
        v = e->getOrig()->getId();
        u = e->getDest()->getId();

        GraphViewer::Edge &edge = gv.addEdge(idEdge, gv.getNode(u), gv.getNode(v), GraphViewer::Edge::DIRECTED);

        std::vector<Truck*> trucks = e->getPassedTrucks();

        if (trucks.size() == 0){
            edge.setColor(GraphViewer::BLACK);
            edge.setThickness(0.00001);
        }
        else if (trucks.size() == 1){
            edge.setColor(trucks.at(0)->getColor());
            edge.setThickness(0.00005);
        }
        else{
            edge.setColor(GraphViewer::RED);
            edge.setThickness(0.00005);
        }

        idEdge++;
    }

    if (graphFile.getbackGroundImage() != "") {
        gv.setBackground(
                graphFile.getbackGroundImage(),
                sf::Vector2f(-8.7817, -41.3095), // TODO this values by attribute?
                sf::Vector2f(1.3297, 1.0) / 7010.0f,
                0.8
        );
    }

/*
    gv.setEnabledNodes(false); // Disable node drawing
    gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);
*/

    gv.createWindow(1600, 900);
    gv.join();
}
