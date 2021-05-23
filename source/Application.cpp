#include <iostream>
#include <string>

#include "Application.h"
#include "View/View.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "MultiDepotVehicleRouting.h"
#include "algorithms/shortest-path/AStar.h"
#include "algorithms/shortest-path/Dijkstra.h"

using namespace std;

Application::Application(const string &files_root) : graphFiles(files_root) {}

void Application::run() {
    bool exit = false;
    this->selectMap();

    while (!exit) {
        this->selectOperation();

        string ans;
        while (true) {
            cout << "Enter one of the following: select_map, select_operation, exit.\n";
            cout << "> ";
            cin >> ans;

            if(cin.fail()){
                cin.clear();
                cin.ignore(9999, '\n');
                continue;
            }
            cin.ignore(9999, '\n');

            if(ans == "select_map") {
                this->selectMap();
                break;
            } else if(ans == "select_operation") {
                break;
            } else if (ans == "exit") {
                exit = true;
                break;
            } else {
                cout << "Unknown option" << endl;
            }
        }
    }
}


void Application::selectMap() {
    string ans;
    while (true) {
        cout << "Select one of the following maps: porto, porto_strong, penafiel, penafiel_strong, espinho, espinho_strong.\n"; //TODO
        cout << "> ";
        cin >> ans;

        if(cin.fail()){
            cin.clear();
            cin.ignore(9999, '\n');
            continue;
        }
        cin.ignore(9999, '\n');

        if (ans == "porto") {
            this->graphFileSelected = this->graphFiles.getPorto();
        } else if (ans == "porto_strong") {
            this->graphFileSelected = this->graphFiles.getPortoStrongComponent();
        } else if (ans == "penafiel") {
            this->graphFileSelected = this->graphFiles.getPenafiel();
        } else if (ans == "penafiel_strong") {
            this->graphFileSelected = this->graphFiles.getPenafielStrongComponent();
        } else if (ans == "espinho") {
            this->graphFileSelected = this->graphFiles.getEspinho();
        } else if (ans == "espinho_strong") {
            this->graphFileSelected = this->graphFiles.getEspinhoStrongComponent();
        } else {
            cout << "Unknown map" << endl;
            continue;
        }

        view(graphFileSelected, DISTRIBUTION);
        break;
    }
}


void Application::selectOperation() {
    string ans;
    while (true) {
        cout << "Select one of the following operations: scc, distribute_vaccines, shortest_path.\n";
        cout << "> ";
        cin >> ans;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            continue;
        }
        cin.ignore(9999, '\n');

        if (ans == "scc") {
            this->calculateAndShowSCC();
            break;
        } else if (ans == "distribute_vaccines") {
            this->distributeSubMenu();
            break;
        } else if (ans == "shortest_path") {
            this->shortestPathSubMenu(); //
            break;
        }
        else {
            cout << "Unknown operation on map" << endl;
            continue;
        }

    }
}

void Application::shortestPathSubMenu(){
    Graph *graph = this->graphFileSelected->getGraph();

    size_t source, dest;

    Vertex *s;
    Vertex *d;

    while (true) {
        cout << "Insert source id and destination id: <source> <destination>\n";
        cout << "> ";
        cin >> source >> dest;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            continue;
        }
        cin.ignore(9999, '\n');

        s = graph->findVertex(source);
        d = graph->findVertex(dest);

        if (s == nullptr || d == nullptr) {
            cout << "Invalid ids\n";
        } else {
            break;
        }
    }

    string shortestAlgo;

    while (true) {
        cout << "What algorithm do you wish to use? dijkstra or astar\n";
        cout << "> ";
        cin >> shortestAlgo;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            continue;
        }
        cin.ignore(9999, '\n');

        if (shortestAlgo == "dijkstra") {
            dijkstraAndShow(s, d);
            break;
        }
        else if (shortestAlgo == "astar"){
            aStarAndShow(s, d);
            break;
        }
        else {
            cout << "Invalid input\n";
        }
    }

}



void Application::calculateAndShowSCC() {
    Kosaraju kosaraju;
    kosaraju.run(this->graphFileSelected->getGraph());

    size_t idx = 0;
    size_t max = 0;
    vector<std::size_t > sccMap = kosaraju.getMap();
    for (int i = 0; i < sccMap.size(); i++) {
        if (sccMap[i] > max) {
            idx = i;
            max = sccMap[i];
        }
    }

    view(this->graphFileSelected, SCC, idx);
}


void Application::distributeSubMenu() {
    double timeLim;
    bool passTimeLim = false;

    while (true) {
        cout << "How much is the time limit?\n";
        cout << "> ";
        cin >> timeLim;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            continue;
        }
        cin.ignore(9999, '\n');

        if (timeLim > 0) {
            break;
        } else {
            cout << "Invalid time" << endl;
            continue;
        }
    }

    while (true) {
        cout << "Should the truck pass the time if the it is found to be impossible to comply with the time limit? (0/1)\n";
        cout << "> ";
        cin >> passTimeLim;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Invalid input" << endl;
            continue;
        }
        cin.ignore(9999, '\n');

        this->distributeAndShow(timeLim, passTimeLim);
        break;

    }
}


void Application::distributeAndShow(double timeLim, bool passTimeLim) {
    multiDepotVehicleRouting(this->graphFileSelected, timeLim, passTimeLim);
    view(this->graphFileSelected, DISTRIBUTION);
    this->graphFileSelected->reset();
}


void Application::aStarAndShow(Vertex *source, Vertex *dest) {
    Graph *graph = this->graphFileSelected->getGraph();

    AStar aStar(graph, source, dest);
    aStar.run();
    if (aStar.getPath().empty())
        cout << "No possible path\n";
    cout << "A* vertex count viewed: " << aStar.getVertexViewedCount() << endl;

    view(this->graphFileSelected, SHORTEST_PATH);
}

void Application::dijkstraAndShow(Vertex *source, Vertex *dest) {
    Graph *graph = this->graphFileSelected->getGraph();

    Dijkstra dijkstra;
    dijkstra.initialize(graph, source->getId());
    dijkstra.find(dest->getId());
    if (dijkstra.getPath().at(dest) == nullptr)
        cout << "No possible path\n";
    cout << "Dijkstra vertex count viewed: " << dijkstra.getVertexViewedCount() << endl;
    view(this->graphFileSelected, SHORTEST_PATH);
}

