#include <iostream>
#include <chrono>

#include "Graph.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "algorithms/acessibility/BreathFirstSearch.h"
#include "algorithms/acessibility/DepthFirstSearch.h"

#include "GraphFiles.h"

#include "View/View.h"


#define FILES_ROOT "../maps" // TODO define properly (not needed now)

using namespace std;

int main() {
    GraphFiles graphFiles(FILES_ROOT);
    /// GraphFile Portugal = graphFiles.getPortugal();
    GraphFile Porto = graphFiles.getPortugal();
    Graph g = Porto.getGraph();

    Kosaraju kosaraju;
    BreathFirstSearch bfs;
    DepthFirstSearch dfs;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    dfs.run(g);

    auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as a double.
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms";

    /*
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    kosaraju.run(g);
    auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as a double.
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_double.count() << "ms";
     */

    //view(Porto);

    return 0;

    /*
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
    */
    // return 0;
}

