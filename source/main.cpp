#include <iostream>

#include "Graph.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "GraphFiles.h"
#include "View/View.h"

#define FILES_ROOT "../maps" // TODO define properly (not needed now)

using namespace std;

int main() {
    GraphFiles graphFiles(FILES_ROOT);
    GraphFile Portugal = graphFiles.getPorto();
    view(Portugal);

    return 0;
}

