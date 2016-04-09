cmake_minimum_required (VERSION 3.1)

set (PROJECT my_set)
project (${PROJECT})

set (HEADERS
    my_set.hpp)

set (SOURCES
    my_set.hpp
    main.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 11)

# TODO enable support of static libraries in the next lines
#
# add_library(my_set_lb STATIC ${SOURCE_LIB})
# add_executable(${PROJECT} ${SOURCE_EXE})
# target_link_libraries(${PROJECT} my_set_lb)
