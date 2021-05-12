#include <gtest/gtest.h>
#include "../Graph.h"
#include "../ConectividadeForte/Kosaraju.h"
#include "../ConectividadeForte/Tarjan.h"

#include <iostream>

using namespace std;


TEST(Tests_Test1, testKosaraju1) {
    Graph g;

    vector< vector< Vertex* > > correct;

    vector<Vertex*> scc1;
    vector<Vertex*> scc2;
    vector<Vertex*> scc3;
    vector<Vertex*> scc4;

    scc1.push_back(g.addVertex(7));

    scc2.push_back(g.addVertex(8));

    scc3.push_back(g.addVertex(0));
    scc3.push_back(g.addVertex(3));
    scc3.push_back(g.addVertex(2));
    scc3.push_back(g.addVertex(1));

    scc4.push_back(g.addVertex(4));
    scc4.push_back(g.addVertex(6));
    scc4.push_back(g.addVertex(5));

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

    correct.push_back(scc1);
    correct.push_back(scc2);
    correct.push_back(scc3);
    correct.push_back(scc4);

    vector<vector<Vertex*>> result = kosaraju(g);

    EXPECT_EQ(correct, result);
}


TEST(Tests_Test2, testKosaraju2) {
    Graph<int> g;

    vector< vector< Vertex<int>* > > correct;

    vector<Vertex<int>*> scc1;
    vector<Vertex<int>*> scc2;
    vector<Vertex<int>*> scc3;
    vector<Vertex<int>*> scc4;
    vector<Vertex<int>*> scc5;

    scc1.push_back(g.addVertex(1));

    scc2.push_back(g.addVertex(2));
    scc2.push_back(g.addVertex(5));

    scc3.push_back(g.addVertex(4));

    scc4.push_back(g.addVertex(3));
    scc4.push_back(g.addVertex(6));

    scc5.push_back(g.addVertex(7));
    scc5.push_back(g.addVertex(8));
    scc5.push_back(g.addVertex(9));
    scc5.push_back(g.addVertex(10));
    scc5.push_back(g.addVertex(11));
    scc5.push_back(g.addVertex(12));

    g.addEdge(1, 2, 0, 0);
    g.addEdge(2, 3, 0, 0);
    g.addEdge(2, 4, 0, 0);
    g.addEdge(3, 6, 0, 0);
    g.addEdge(5, 2, 0, 0);
    g.addEdge(5, 7, 0, 0);
    g.addEdge(6, 3, 0, 0);
    g.addEdge(6, 8, 0, 0);
    g.addEdge(7, 8, 0, 0);
    g.addEdge(7, 10, 0, 0);
    g.addEdge(8, 11, 0, 0);
    g.addEdge(9, 7, 0, 0);
    g.addEdge(10, 9, 0, 0);
    g.addEdge(11, 12, 0, 0);
    g.addEdge(12, 10, 0, 0);

    vector<vector<Vertex<int>*>> result = kosaraju(g);

    EXPECT_EQ(correct, result);
}

TEST(Tests_Test1, testTarjan1) {
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

    vector<vector<Vertex<int>*>> result = tarjan(g);

    EXPECT_EQ(correct, result);
}
