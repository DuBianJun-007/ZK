cmake_minimum_required(VERSION 3.14)
project(ZK_StringMatching VERSION 1.0.0 LANGUAGES CXX)

# C++17 required for std::filesystem and std::chrono
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform-specific settings
if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -O2)
endif()

# Source files for the algorithm library
set(ALGORITHM_SOURCES
    src/force.cpp
    src/kmp.cpp
    src/bm.cpp
    src/bmh.cpp
    src/sunday.cpp
    src/zk2.cpp
    src/zk2_ascii.cpp
    src/zk2_utf.cpp
    src/zk3.cpp
    src/zk3_utf.cpp
    src/benchmark.cpp
)

set(ALGORITHM_HEADERS
    src/force.h
    src/kmp.h
    src/bm.h
    src/bmh.h
    src/sunday.h
    src/zk2.h
    src/zk2_ascii.h
    src/zk2_utf.h
    src/zk3.h
    src/zk3_utf.h
    src/benchmark.h
)

# Static library for the algorithms
add_library(zk_algorithms STATIC ${ALGORITHM_SOURCES} ${ALGORITHM_HEADERS})
target_include_directories(zk_algorithms PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Demo executable
add_executable(zk_demo examples/demo.cpp)
target_link_libraries(zk_demo zk_algorithms)

# Install rules
install(TARGETS zk_algorithms ARCHIVE DESTINATION lib)
install(FILES ${ALGORITHM_HEADERS} DESTINATION include/zk)
install(TARGETS zk_demo RUNTIME DESTINATION bin)
