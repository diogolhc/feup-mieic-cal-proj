#include <iostream>

#include "Graph.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "GraphFiles.h"
#include "View/View.h"


#define FILES_ROOT "../maps" // TODO define properly (not needed now)

using namespace std;

int main() {
    GraphFiles graphFiles(FILES_ROOT);
    /// GraphFile Portugal = graphFiles.getPortugal();
    GraphFile Porto = graphFiles.getPorto();
    Graph g = Porto.getGraph();

    Kosaraju kosaraju;
    kosaraju.kosaraju(g);

    vector<int> mp = kosaraju.getMap();

    int max = 0;
    int index = -1;
    for ( int i = 0; i < mp.size(); i++) {
        if (mp[i] > max) {
            max = mp[i];
            index = i;
        }
    }

    cout << "MAX: " << max << " index: " << index << endl;
    // view(Porto);

    return 0;
}

