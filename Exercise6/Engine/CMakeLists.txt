# Engine Only

file(GLOB_RECURSE MyEngine-src "*.cpp")
file(GLOB_RECURSE MyEngine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)

add_library(Ex6MyEngine ${MyEngine-src} ${MyEngine-hpp})
target_link_libraries(Ex6MyEngine ${SGE_LIBRARIES})

target_include_directories(Ex6MyEngine PUBLIC "Engine")
target_include_directories(Ex6MyEngine PUBLIC "3rdParty")
