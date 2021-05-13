//
// Created by sense on 12/05/2021.
//

#include <gtest/gtest.h>
#include "../Graph.h"
#include "../algorithms/shortest-path/Dijkstra.h"

#include <iostream>
#include <unordered_map>

using namespace std;

TEST(Tests_dijkstra, test_1){
    Graph graph;

    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);

    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 2);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 3);
    graph.addEdge(1, 3, 6);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 5, 1);

    Dijkstra dijkstra;
    dijkstra.initialize(&graph, 0);
    dijkstra.run();
    unordered_map<Vertex *, Vertex *> path = dijkstra.getPath();

    EXPECT_EQ(path.at(graph.findVertex(1))->getId(), 0);
    EXPECT_EQ(path.at(graph.findVertex(2))->getId(), 0);
    EXPECT_EQ(path.at(graph.findVertex(3))->getId(), 1);
    EXPECT_EQ(path.at(graph.findVertex(4))->getId(), 2);
    EXPECT_EQ(path.at(graph.findVertex(5))->getId(), 4);

}