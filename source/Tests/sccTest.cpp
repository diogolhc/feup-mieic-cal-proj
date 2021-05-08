#include <gtest/gtest.h>
#include "../Graph.h"
#include "../ConectividadeForte/Kosaraju.h"
#include <iostream>

using namespace std;

TEST(Tests_Test1, testKosaraju1) {
    Graph<int> g;

    vector< vector< Vertex<int>* > > correct;

    vector<Vertex<int>*> scc1;
    vector<Vertex<int>*> scc2;
    vector<Vertex<int>*> scc3;
    vector<Vertex<int>*> scc4;

    scc1.push_back(g.addVertex(7));

    scc2.push_back(g.addVertex(8));

    scc3.push_back(g.addVertex(0));
    scc3.push_back(g.addVertex(3));
    scc3.push_back(g.addVertex(2));
    scc3.push_back(g.addVertex(1));

    scc4.push_back(g.addVertex(4));
    scc4.push_back(g.addVertex(6));
    scc4.push_back(g.addVertex(5));

    g.addEdge(0, 3, 0, 0);
    g.addEdge(3, 2, 0, 0);
    g.addEdge(2, 1, 0, 0);
    g.addEdge(1, 0, 0, 0);
    g.addEdge(4, 2, 0, 0);
    g.addEdge(5, 4, 0, 0);
    g.addEdge(4, 6, 0, 0);
    g.addEdge(6, 5, 0, 0);
    g.addEdge(6, 7, 0, 0);
    g.addEdge(8, 7, 0, 0);

    vector<vector<Vertex<int>*>> result = kosaraju(g);

    EXPECT_EQ(correct, result);
}

