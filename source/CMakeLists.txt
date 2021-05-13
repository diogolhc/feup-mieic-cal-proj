cmake_minimum_required(VERSION 3.17)
project(source)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_STANDARD 14)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

# Add the Test files
file(GLOB Tests_FILES CONFIGURE_DEPENDS
        "Tests/*.cpp"
        )

file(GLOB View_FILES CONFIGURE_DEPENDS
        "View/*.cpp"
        )

file(GLOB Algorithm_FILES CONFIGURE_DEPENDS
        "Graph.cpp"
        "algorithms/acessibility/DepthFirstSearch.cpp"
        "algorithms/acessibility/BreathFirstSearch.cpp"
        "algorithms/strongly-connected-components/Kosaraju.cpp"
        "algorithms/strongly-connected-components/Tarjan.cpp"
        "algorithms/shortest-path/Dijkstra.cpp"
        "algorithms/shortest-path/AStar.cpp"
        "algorithms/shortest-path/FloydWarshall.cpp"
        "algorithms/travelling-salesman/BellmanHelpKarp.cpp"
        "algorithms/travelling-salesman/NearestNeighbor.cpp"
        "algorithms/vehicle-routing/MultiSourceDijkstra.cpp"
        )

add_executable(source main.cpp
        GraphFiles.cpp
        View/View.cpp
        ${Algorithm_FILES}
        ${View_FILES}
        GraphFiles.cpp
        )

add_executable(Tests
        ${Tests_FILES}
        ${Algorithm_FILES}
        )

add_executable(View
        ${Algorithm_FILES}
        ${View_FILES}
        GraphFiles.cpp
        )

target_link_libraries(View graphviewer)
target_link_libraries(Tests gtest_main gmock_main)
target_link_libraries(source graphviewer)
