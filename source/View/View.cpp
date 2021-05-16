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
                node.setColor(GraphViewer::GREEN);
                break;
            case APPLICATION_CENTER:
                node.setColor(GraphViewer::YELLOW);
                break;
        }

    }

    GraphViewer::id_t idEdge = 0, u, v;
    for (Edge *e : graph.getEdges()) {
        u = e->getOrig()->getId();
        v = e->getDest()->getId();
        GraphViewer::Edge &edge = gv.addEdge(idEdge, gv.getNode(u), gv.getNode(v), GraphViewer::Edge::DIRECTED);

        if (e->getPassedVehicle()) {
            if (e->getDest()->getCluster() == 53578 && 53578 == e->getOrig()->getCluster()) // TODO this is just to debug
                edge.setColor(GraphViewer::BLUE);
            else if (e->getDest()->getCluster() == 11847 && 11847 == e->getOrig()->getCluster())
                edge.setColor(GraphViewer::MAGENTA);
            edge.setThickness(0.00004);
        } else {
            if (e->getDest()->getCluster() == 53578 && 53578 == e->getOrig()->getCluster()) // TODO this is just to debug
                edge.setColor(GraphViewer::BLUE);
            else if (e->getDest()->getCluster() == 11847 && 11847 == e->getOrig()->getCluster())
                edge.setColor(GraphViewer::MAGENTA);
            //edge.setColor(GraphViewer::RED);
            edge.setThickness(0.00001);
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
