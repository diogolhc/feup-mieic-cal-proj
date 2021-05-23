cmake_minimum_required(VERSION 3.17)
project(source)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_STANDARD 14)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

file(GLOB View_FILES CONFIGURE_DEPENDS
        "View/*.cpp"
        )

file(GLOB Algorithm_FILES CONFIGURE_DEPENDS
        "Graph.cpp"
        "agents/ApplicationCenter.cpp"
        "agents/StorageCenter.cpp"
        "agents/Truck.cpp"
        "GraphFiles.cpp"
        "algorithms/acessibility/DepthFirstSearch.cpp"
        "algorithms/acessibility/BreathFirstSearch.cpp"
        "algorithms/strongly-connected-components/Kosaraju.cpp"
        "algorithms/strongly-connected-components/Tarjan.cpp"
        "algorithms/shortest-path/Dijkstra.cpp"
        "algorithms/shortest-path/AStar.cpp"
        "algorithms/travelling-salesman/NearestNeighbor.cpp"
        "algorithms/vehicle-routing/MultiSourceDijkstra.cpp"
        )

add_executable(source main.cpp
        View/View.cpp
        ${Algorithm_FILES}
        ${View_FILES}
        Application.cpp Application.h MultiDepotVehicleRouting.cpp MultiDepotVehicleRouting.h)

add_executable(View
        ${Algorithm_FILES}
        ${View_FILES}
        GraphFiles.cpp
        )

target_link_libraries(View graphviewer)
target_link_libraries(source graphviewer)
