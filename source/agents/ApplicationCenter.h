//
// Created by sense on 16/05/2021.
//

#ifndef SOURCE_APPLICATIONCENTER_H
#define SOURCE_APPLICATIONCENTER_H

#include "../Graph.h"

class ApplicationCenter {
    Vertex * vertex;
    int vaccinesNeeded;
public:
    explicit ApplicationCenter(Vertex * vertex1);
    explicit ApplicationCenter(Vertex * vertex1, int vaccines);
    Vertex * getVertex() const;
    int getVaccinesNeeded() const;
};


struct SortByLat {
    bool operator() (ApplicationCenter * left,  ApplicationCenter * right) const;
};

struct SortByLng {
    bool operator() (ApplicationCenter * left,  ApplicationCenter * right) const;
};

#endif //SOURCE_APPLICATIONCENTER_H
