#ifndef SOURCE_APPLICATION_H
#define SOURCE_APPLICATION_H

#include <string>
#include "GraphFiles.h"


class Application {
private:
    GraphFiles graphFiles;
    GraphFile* graphFileSelected = nullptr;

    void selectMap();
    void selectOpearation();
    void calculateAndShowSCC();
    void distributeSubMenu();
    void distributeAndShow(double timeLim);
    void aStarSubMenu();
    void aStarAndShow(Vertex *source, Vertex *dest);
public:
    explicit Application(const string &files_root);
    void run();

};


#endif //SOURCE_APPLICATION_H
