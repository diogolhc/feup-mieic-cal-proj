#ifndef SOURCE_APPLICATION_H
#define SOURCE_APPLICATION_H

#include <string>
#include "GraphFiles.h"


class Application {
private:
    GraphFiles graphFiles;
    GraphFile* graphFileSelected = nullptr;

    void selectMap();
    void selectOperation();
    void calculateAndShowSCC();
    void distributeSubMenu();
    void distributeAndShow(double timeLim, bool passTimeLim);
    void aStarAndShow(Vertex *source, Vertex *dest);
    void dijkstraAndShow(Vertex *source, Vertex *dest);
    void shortestPathSubMenu();
public:
    explicit Application(const string &files_root);
    void run();

};


#endif //SOURCE_APPLICATION_H
