cmake_minimum_required(VERSION 3.5)
project(Soplon CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    if (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
        set(CMAKE_CXX_STANDARD 20)
    elseif (HAS_ANY AND HAS_STRING_VIEW)
        set(CMAKE_CXX_STANDARD 17)
    else ()
        set(CMAKE_CXX_STANDARD 14)
    endif ()
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)


# vcpkg ou system packages
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# MySQL X DevAPI (via vcpkg ou system)
find_package(unofficial-mysql-connector-cpp CONFIG QUIET)
if (unofficial-mysql-connector-cpp_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::mysql-connector-cpp::connector)
else ()
    # Linux fallback (apt install libmysqlcppconn8-dev)
    find_package(PkgConfig QUIET)
    if (PkgConfig_FOUND)
        pkg_check_modules(MYSQLX REQUIRED IMPORTED_TARGET mysqlcppconn8)
        target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::MYSQLX)
    else ()
        message(FATAL_ERROR "MySQL X DevAPI not found - install via vcpkg or apt")
    endif ()
endif ()

# Boost pour C++14 fallback
if (CMAKE_CXX_STANDARD LESS 17)
    message(STATUS "Using Boost for C++14 compatibility")
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "Using C++17")
else ()
    message(STATUS "Using C++20")
endif ()

# Sources Drogon
aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(sources SOPLON_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/models
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CTL_SRC}
        ${FILTER_SRC}
        ${PLUGIN_SRC}
        ${MODEL_SRC}
        ${SOPLON_SRC}
)

add_subdirectory(test)