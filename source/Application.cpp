#include <iostream>
#include <string>

#include "Application.h"
#include "View/View.h"
#include "algorithms/strongly-connected-components/Kosaraju.h"
#include "MultiDepotVehicleRouting.h"
#include "algorithms/shortest-path/AStar.h"

using namespace std;


Application::Application(const string &files_root) : graphFiles(files_root) {}

/**
 * TODO os grafos não estão a dar o reset necessário para dar para fazer varias vezes a distribuição no mesmo grafo
 */

void Application::run() {
    bool exit = false;
    this->selectMap();

    while (!exit) {
        this->selectOpearation();

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

        view(graphFileSelected, DISTRIBUTION); // TODO add another state for VANILLA
        break;
    }
}


void Application::selectOpearation() {
    string ans;
    while (true) {
        cout << "Select one of the following operations: scc, distribute_vaccines, shortest_path.\n"; //TODO
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
            this->aStarSubMenu(); // TODO add shortestPathSubMenu() if Dijkstra can be called from interface so that user can choose which one to call
            break;
        } // TODO add the rest
        else {
            cout << "Unknown operation on map" << endl;
            continue;
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
            this->distributeAndShow(timeLim);
            break;
        } else {
            cout << "Invalid time" << endl;
            continue;
        }
    }
}


void Application::distributeAndShow(double timeLim) {
    multiDepotVehicleRouting(this->graphFileSelected, timeLim);
    view(this->graphFileSelected, DISTRIBUTION);
}


void Application::aStarSubMenu() {
    Graph *graph = this->graphFileSelected->getGraph();

    size_t source, dest;
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

        Vertex *s = graph->findVertex(source);
        Vertex *d = graph->findVertex(dest);

        if (s == nullptr || d == nullptr) {
            cout << "Invalid ids\n";
        } else {
            this->aStarAndShow(s, d);
            break;
        }

    }
}


void Application::aStarAndShow(Vertex *source, Vertex *dest) {
    Graph *graph = this->graphFileSelected->getGraph();

    AStar aStar(graph, source, dest);
    aStar.run();
    if (aStar.getPath().empty())
        cout << "No possible path\n";
    cout << "A* vertex count viewed: " << aStar.getVertexViewedCount() << endl;
    // TODO fazer semelhante ao Dijkstra para dar para comparar tempos de execução e vertices analizados de modo a tirar umas conclusões empiricas para o relatório

    view(this->graphFileSelected, SHORTEST_PATH);
}

