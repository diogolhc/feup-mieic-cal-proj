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

file(GLOB ConectividadeForte_FILES CONFIGURE_DEPENDS
        "ConectividadeForte/*.cpp"
        )


add_executable(Tests
        ${Tests_FILES}
        )

add_executable(View
        ${View_FILES}
        )

add_executable(ConectividadeForte
        ${ConectividadeForte_FILES}
        )

add_executable(source main.cpp)

target_link_libraries(Tests gtest_main gmock_main)
target_link_libraries(View graphviewer)
target_link_libraries(ConectividadeForte graphviewer)

target_include_directories(Tests PRIVATE ${Tests_FILES})
