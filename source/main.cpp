#include <iostream>

#include "Graph.h"
#include "GraphFiles.h"
#include "View/View.h"

#define FILES_ROOT "../../../maps" // TODO define properly (not needed now)

using namespace std;


int main() {
    GraphFiles graphFiles(FILES_ROOT);
    GraphFile Portugal = graphFiles.getPortugal();
    view(Portugal);

    return 0;
}

