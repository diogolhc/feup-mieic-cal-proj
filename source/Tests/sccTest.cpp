#include <gtest/gtest.h>
#include "../Graph.h"

TEST(Tests_Test1, testKosaraju1) {
    Graph<string> g;

    g.addVertex("s");
    g.addVertex("x");
    g.addVertex("t");

    g.addEdge("s", "t", 3, 1);
    g.addEdge("s", "x", 2, 2);
    g.addEdge("x", "t", 1, 2);

    double cost = g.minCostFlow("s", "t", INF);

    EXPECT_EQ(cost, 7);

    EXPECT_EQ(g.getFlow("s", "t"), 3);
    EXPECT_EQ(g.getFlow("s", "x"), 1);
    EXPECT_EQ(g.getFlow("x", "t"), 1);
}

