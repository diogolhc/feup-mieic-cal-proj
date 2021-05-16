#include <iostream>

#include "algorithms/travelling-salesman/NearestNeighbor.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "Graph.h"
#include "GraphFiles.h"
#include "View/View.h"


#define FILES_ROOT "../maps" // TODO define properly (not needed now)

using namespace std;

int main() {
    GraphFiles graphFiles(FILES_ROOT);
    /// GraphFile Portugal = graphFiles.getPortugal();
    GraphFile Porto = graphFiles.getPortoStrongComponent();

    Graph graph = Porto.getGraph();

    vector<int> application_center_ids;
    int origin_id;

    for (Vertex * vertex : graph.getVertexSet()){
        if (vertex->getType() == APPLICATION_CENTER){
            application_center_ids.push_back(vertex->getId());
        }
        else if (vertex->getType() == STORAGE_CENTER){
            origin_id = vertex->getId();
        }
    }

    NearestNeighbor nearestNeighbor;

    nearestNeighbor.initialize(&graph, origin_id, application_center_ids);
    vector<Vertex *> res = nearestNeighbor.run();

    for (Vertex * vertex : res){
        if (vertex->getType() != NONE){
            cout << "Id: " << vertex->getId() << " XY: " << vertex->getCoordinates().lat
            << " " <<vertex->getCoordinates().lon << " AC? " << (vertex->getType() == APPLICATION_CENTER) << endl;
        }
    }

    view(Porto);
    return 0;
}

