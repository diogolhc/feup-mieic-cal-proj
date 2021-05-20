#include "Application.h"

#define FILES_ROOT "../maps"

int main() {
    srand(time(0));

    Application application(FILES_ROOT);
    application.run();

    return 0;
}
