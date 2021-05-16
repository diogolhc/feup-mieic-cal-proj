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
    explicit ApplicationCenter(Vertex * vertex);
    Vertex * getVertex() const;
};


#endif //SOURCE_APPLICATIONCENTER_H
