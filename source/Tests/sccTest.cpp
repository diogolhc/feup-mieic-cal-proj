#include <gtest/gtest.h>
#include "../Graph.h"

TEST(Tests_Test1, testKosaraju1) {
    Graph<int> g;

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);


    g.addEdge(1, 3, 3, 1);
    g.addEdge(1, 2, 2, 2);
    g.addEdge(3, 4, 1, 2);

    double cost = g.minCostFlow(1, 3, INF);

    EXPECT_EQ(cost, 7);

    EXPECT_EQ(g.getFlow(1, 3), 3);
    EXPECT_EQ(g.getFlow(1, 2), 1);
    EXPECT_EQ(g.getFlow(2, 3), 1);
}

