cmake_minimum_required(VERSION 3.10)
project(Snake)

# It's better to explicitly list source files rather than using GLOB
set(SOURCES
    item.cpp
    player.cpp
    main.cpp
)

set(HEADERS
    config.h
    ITUGames.h
    position.h
    item.h
    player.h
)

add_executable(SnakeGame ${SOURCES} ${HEADERS})

target_link_libraries(SnakeGame ${SGE_LIBRARIES})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    # Copy dll's to output path
    file(COPY ${SGE_LIBRARIES_SHARED} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()