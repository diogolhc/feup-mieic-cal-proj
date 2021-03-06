#include <iostream>
#include "View.h"
#include "graphviewer.h"
#include "../algorithms/strongly-connected-components/Kosaraju.h"


void viewDistribution(GraphViewer &gv, const Graph *graph) {

    GraphViewer::id_t idNode;
    double lat, lon;
    for (Vertex *v : graph->getVertexSet()) {
        idNode = v->getId();
        lat = v->getCoordinates().lat;
        lon = v->getCoordinates().lon;
        GraphViewer::Node &node = gv.addNode(idNode, sf::Vector2f(lon, -lat));
        node.setOutlineThickness(0.0);
        node.setSize(0.001);

        switch (v->getType()) {
            case NONE:
                node.setSize(0.0);
                break;
            case STORAGE_CENTER:
                node.setColor(GraphViewer::GREEN);
                break;
            case APPLICATION_CENTER:
                node.setColor(GraphViewer::YELLOW);
                break;
            case NOT_REACHABLE_AC:
                node.setColor(GraphViewer::RED);
                break;
            case NOT_USED_SC:
                node.setColor(GraphViewer::ORANGE);
                break;
        }
    }

    GraphViewer::id_t idEdge = 0, u, v;
    for (Edge *e : graph->getEdges()) {
        u = e->getOrig()->getId();
        v = e->getDest()->getId();

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
}


void viewScc(GraphViewer &gv, const Graph *graph, const size_t maxSccComponentIdx) {
    GraphViewer::id_t idNode;

    double lat, lon;

    for (Vertex *v : graph->getVertexSet()) {
        idNode = v->getId();
        lat = v->getCoordinates().lat;
        lon = v->getCoordinates().lon;
        GraphViewer::Node &node = gv.addNode(idNode, sf::Vector2f(lon, -lat));
        node.setOutlineThickness(0.0);
        node.setSize(0.0001);

        if (v->getSCC() == maxSccComponentIdx) {
            gv.getNode(idNode).setColor(GraphViewer::YELLOW);
        } else {
            gv.getNode(idNode).setColor(GraphViewer::BLUE);
        }
    }

    GraphViewer::id_t idEdge = 0, u, v;
    for (Edge *e : graph->getEdges()) {
        u = e->getOrig()->getId();
        v = e->getDest()->getId();

        GraphViewer::Edge &edge = gv.addEdge(idEdge, gv.getNode(u), gv.getNode(v), GraphViewer::Edge::DIRECTED);

        edge.setColor(GraphViewer::BLACK);
        edge.setThickness(0.00005);

        idEdge++;
    }
}

void viewShortestPath(GraphViewer &gv, const Graph *graph) {
    GraphViewer::id_t idNode;

    double lat, lon;

    for (Vertex *v : graph->getVertexSet()) {
        idNode = v->getId();
        lat = v->getCoordinates().lat;
        lon = v->getCoordinates().lon;
        GraphViewer::Node &node = gv.addNode(idNode, sf::Vector2f(lon, -lat));
        node.setOutlineThickness(0.0);

        if (v->getVisited()) {
            node.setColor(GraphViewer::GREEN);
            node.setSize(0.0001);
        } else {
            node.setSize(0.0);
        }

    }

    GraphViewer::id_t idEdge = 0, u, v;
    for (Edge *e : graph->getEdges()) {
        u = e->getOrig()->getId();
        v = e->getDest()->getId();

        GraphViewer::Edge &edge = gv.addEdge(idEdge, gv.getNode(u), gv.getNode(v), GraphViewer::Edge::DIRECTED);

        if (e->getPassedShortestPath()) {
            edge.setColor(GraphViewer::RED);
            edge.setThickness(0.00003);
        } else {
            edge.setColor(GraphViewer::BLACK);
            edge.setThickness(0.00001);
        }

        idEdge++;
    }
}


void view(GraphFile *graphFile, const viewState &state, size_t maxSccComponentIdx) {
    Graph *graph = graphFile->getGraph();
    Coordinates centralCoord = graphFile->getCentralCoordinates();
    GraphViewer gv;
    gv.setScale(graphFile->getScale());
    gv.setCenter(sf::Vector2f(centralCoord.lon, -centralCoord.lat));

    switch (state) {
        case SCC:
            viewScc(gv, graph, maxSccComponentIdx);
            break;
        case DISTRIBUTION:
            viewDistribution(gv, graph);
            break;
        case SHORTEST_PATH:
            viewShortestPath(gv, graph);
            break;
    }

    if (graphFile->getBackGroundImage() != "") {
        gv.setBackground(
                graphFile->getBackGroundImage(),
                sf::Vector2f(-8.7817, -41.3095),
                sf::Vector2f(1.3297, 1.0) / 7010.0f,
                0.8
        );
    }

    gv.createWindow(1600, 900);
    gv.join();
}

