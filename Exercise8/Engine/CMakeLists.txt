# Engine Only

file(GLOB_RECURSE MyEngine-src "*.cpp")
file(GLOB_RECURSE MyEngine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)


add_library(Ex8MyEngine ${MyEngine-src} ${MyEngine-hpp})

target_link_libraries(Ex8MyEngine ${SGE_LIBRARIES})

target_include_directories(Ex8MyEngine PUBLIC ${MYENGINE_INCLUDE_DIR})
target_include_directories(Ex8MyEngine PUBLIC "3rdParty")
