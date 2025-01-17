cmake_minimum_required(VERSION 3.15)

project(duck_charmer)

set(${PROJECT_NAME}_headers
        convert.hpp
        spaces.hpp
        wrapper_client.hpp
        wrapper_collection.hpp
        wrapper_database.hpp
        wrapper_cursor.hpp
        wrapper_dispatcher.hpp
        wrapper_document.hpp
)

set(${PROJECT_NAME}_sources
        convert.cpp
        main.cpp
        spaces.cpp
        wrapper_client.cpp
        wrapper_collection.cpp
        wrapper_database.cpp
        wrapper_cursor.cpp
        wrapper_dispatcher.cpp
        wrapper_document.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}
)

pybind11_add_module(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        ${CONAN_LIBS}
        rocketjoe::log
        rocketjoe::storage
        rocketjoe::cursor
        rocketjoe::session
        rocketjoe::document
        rocketjoe::dispatcher
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET "hidden")

if (DEV_MODE)
    file(GLOB PY_TESTS
        "test/*.py"
    )
    file(COPY ${PY_TESTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
