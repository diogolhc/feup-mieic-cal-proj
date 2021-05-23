#ifndef SOURCE_VIEW_H
#define SOURCE_VIEW_H

#include "../GraphFiles.h"

enum viewState {
    SCC,
    DISTRIBUTION,
    SHORTEST_PATH
};

void view(GraphFile *graphFile, const viewState &state, size_t maxSccComponentIdx = 0);

#endif //SOURCE_VIEW_H
