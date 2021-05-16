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
    gv.setCenter(sf::Vector2f(centralCoord.lon, -centralCoord.lat)); // TODO pass this to attribute of GraphFile

    GraphViewer::id_t idNode;
    double lat, lon;
    for (Vertex *v : graph.getVertexSet()) {
        idNode = v->getId();
        lat = v->getCoordinates().lat;
        lon = v->getCoordinates().lon;
        GraphViewer::Node &node = gv.addNode(idNode, sf::Vector2f(lon, -lat));
        node.setOutlineThickness(0.0);
        node.setSize(0.0001);
        // TODO colors accordingly to properties
    }

    GraphViewer::id_t idEdge = 0, u, v;
    for (Edge *e : graph.getEdges()) {
        u = e->getOrig()->getId();
        v = e->getDest()->getId();
        GraphViewer::Edge &edge = gv.addEdge(idEdge, gv.getNode(u), gv.getNode(v));
        edge.setThickness(0.0001);

        // TODO colors accordingly to properties
        edge.setColor(GraphViewer::RED);

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


    gv.setEnabledNodes(true); // Disable node drawing
    gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);


    gv.createWindow(1600, 900);
    gv.join();
}
