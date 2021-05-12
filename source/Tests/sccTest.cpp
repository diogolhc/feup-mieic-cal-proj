#include <gtest/gtest.h>
#include "../Graph.h"
#include "../algorithms/strongly-connected-components/Kosaraju.h"

#include <iostream>

using namespace std;

TEST(Tests_Test1, testKosaraju1) {
    Graph g;

    vector<int> scc1;
    vector<int> scc2;
    vector<int> scc3;
    vector<int> scc4;

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);

    scc1.push_back(7);

    scc2.push_back(8);

    scc3.push_back(0);
    scc3.push_back(3);
    scc3.push_back(2);
    scc3.push_back(1);

    scc4.push_back(4);
    scc4.push_back(6);
    scc4.push_back(5);

    g.addEdge(0, 3, 0);
    g.addEdge(3, 2, 0);
    g.addEdge(2, 1, 0);
    g.addEdge(1, 0, 0);
    g.addEdge(4, 2, 0);
    g.addEdge(5, 4, 0);
    g.addEdge(4, 6, 0);
    g.addEdge(6, 5, 0);
    g.addEdge(6, 7, 0);
    g.addEdge(8, 7, 0);

    Kosaraju k;
    k.kosaraju(g);

    EXPECT_NE(g.findVertex(7)->getSCC(), g.findVertex(8)->getSCC());
    EXPECT_NE(g.findVertex(8)->getSCC(), g.findVertex(0)->getSCC());
    EXPECT_NE(g.findVertex(7)->getSCC(), g.findVertex(0)->getSCC());

    EXPECT_EQ(g.findVertex(0)->getSCC(), g.findVertex(3)->getSCC());
    EXPECT_EQ(g.findVertex(3)->getSCC(), g.findVertex(2)->getSCC());
    EXPECT_EQ(g.findVertex(2)->getSCC(), g.findVertex(1)->getSCC());

    EXPECT_EQ(g.findVertex(4)->getSCC(), g.findVertex(6)->getSCC());
    EXPECT_EQ(g.findVertex(6)->getSCC(), g.findVertex(5)->getSCC());

    EXPECT_NE(g.findVertex(0)->getSCC(), g.findVertex(6)->getSCC());
}


TEST(Tests_Test2, testKosaraju2) {
    Graph g;

    vector<int> scc1;
    vector<int> scc2;
    vector<int> scc3;
    vector<int> scc4;
    vector<int> scc5;

    scc1.push_back(1);

    scc2.push_back(2);
    scc2.push_back(5);

    scc3.push_back(4);

    scc4.push_back(3);
    scc4.push_back(6);

    scc5.push_back(7);
    scc5.push_back(8);
    scc5.push_back(9);
    scc5.push_back(10);
    scc5.push_back(11);
    scc5.push_back(12);

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);
    g.addVertex(9);
    g.addVertex(10);
    g.addVertex(11);
    g.addVertex(12);

    g.addEdge(1, 2, 0);
    g.addEdge(2, 3, 0);
    g.addEdge(2, 5, 0);
    g.addEdge(3, 6, 0);
    g.addEdge(5, 2, 0);
    g.addEdge(5, 6, 0);
    g.addEdge(5, 7, 0);
    g.addEdge(6, 3, 0);
    g.addEdge(6, 8, 0);
    g.addEdge(7, 8, 0);
    g.addEdge(7, 10, 0);
    g.addEdge(8, 11, 0);
    g.addEdge(9, 7, 0);
    g.addEdge(10, 9, 0);
    g.addEdge(11, 12, 0);
    g.addEdge(12, 10, 0);

    Kosaraju kosaraju;
    kosaraju.kosaraju(g);

    EXPECT_NE(g.findVertex(1)->getSCC(), g.findVertex(2)->getSCC());
    EXPECT_NE(g.findVertex(1)->getSCC(), g.findVertex(4)->getSCC());
    EXPECT_NE(g.findVertex(1)->getSCC(), g.findVertex(3)->getSCC());
    EXPECT_NE(g.findVertex(1)->getSCC(), g.findVertex(7)->getSCC());
    EXPECT_NE(g.findVertex(2)->getSCC(), g.findVertex(4)->getSCC());
    EXPECT_NE(g.findVertex(2)->getSCC(), g.findVertex(3)->getSCC());
    EXPECT_NE(g.findVertex(2)->getSCC(), g.findVertex(7)->getSCC());
    EXPECT_NE(g.findVertex(4)->getSCC(), g.findVertex(3)->getSCC());
    EXPECT_NE(g.findVertex(4)->getSCC(), g.findVertex(7)->getSCC());
    EXPECT_NE(g.findVertex(3)->getSCC(), g.findVertex(7)->getSCC());

    EXPECT_EQ(g.findVertex(2)->getSCC(), g.findVertex(5)->getSCC());
    EXPECT_EQ(g.findVertex(3)->getSCC(), g.findVertex(6)->getSCC());
    EXPECT_EQ(g.findVertex(7)->getSCC(), g.findVertex(8)->getSCC());
    EXPECT_EQ(g.findVertex(7)->getSCC(), g.findVertex(9)->getSCC());
    EXPECT_EQ(g.findVertex(7)->getSCC(), g.findVertex(10)->getSCC());
    EXPECT_EQ(g.findVertex(7)->getSCC(), g.findVertex(11)->getSCC());
    EXPECT_EQ(g.findVertex(7)->getSCC(), g.findVertex(12)->getSCC());
}

