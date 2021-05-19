//
// Created by sense on 16/05/2021.
//

#ifndef SOURCE_TRUCK_H
#define SOURCE_TRUCK_H

#include <vector>

//#include "ApplicationCenter.h"
#include "graphviewer.h"

class Edge;

static const std::vector<GraphViewer::Color> COLOR_VECTOR = { GraphViewer::GREEN,
                                                              GraphViewer::YELLOW,
                                                              GraphViewer::BLUE,
                                                              GraphViewer::MAGENTA,
                                                              GraphViewer::CYAN,
                                                              GraphViewer::PINK,
                                                              GraphViewer::ORANGE
};

class ApplicationCenter;

class Truck {
    double distanceCovered;
    int vaccinesLeft;
    std::vector<ApplicationCenter *> ACList;
    std::vector<Edge *> edgeList;
    GraphViewer::Color color;
public:
    static const int capacity = 1500;
    explicit Truck(int vaccinesLeft);
    explicit Truck(int vaccinesLeft, const std::vector<ApplicationCenter *> & newACList);
    std::vector<ApplicationCenter *> &getACList();
    void addApplicationCenter(ApplicationCenter * applicationCenter);
    void setACList(const std::vector<ApplicationCenter *> & newACList);
    double getDistanceCovered() const;
    void setDistanceCovered(double distance);
    int getVaccinesLeft() const;
    void addEdge(Edge * edge);
    bool useVaccines(int numVaccines);
    GraphViewer::Color getColor() const;
    void undo();
};


#endif //SOURCE_TRUCK_H
