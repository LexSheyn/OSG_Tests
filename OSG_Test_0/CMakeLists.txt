cmake_minimum_required(VERSION 3.16)

project(osg_0)

set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(IMPORT_STATIC_LIB_DIR  ${CMAKE_SOURCE_DIR}/import/lib/static)
set(IMPORT_DYNAMIC_LIB_DIR ${CMAKE_SOURCE_DIR}/import/lib/dynamic)
set(IMPORT_INCLUDE_DIR     ${CMAKE_SOURCE_DIR}/import/include)

set(IMPORT_LIBRARIES
    libosg.so
    libosgDB.so
    libOpenThreads.so
    libosgUtil.so
    libosgGA.so
    libosgViewer.so)

set(IMPORT_PLUGIN_LIBRARIES
    osgdb_3ds.so)

set(BIN_DIR         ${PROJECT_BINARY_DIR}/bin)
set(STATIC_LIB_DIR  ${PROJECT_BINARY_DIR}/lib/static)
set(DYNAMIC_LIB_DIR ${PROJECT_BINARY_DIR}/lib/dynamic)
set(PDB_DIR         ${PROJECT_BINARY_DIR}/pdb)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${STATIC_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DYNAMIC_LIB_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${PDB_DIR})

set(INCLUDE_DIR                 ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR                  ${CMAKE_SOURCE_DIR}/source)
set(EXPORT_STATIC_LIBRARY_NAME  ${TARGET_NAME}_static_lib)
set(EXPORT_DYNAMIC_LIBRARY_NAME ${TARGET_NAME}_dynamic_lib)

add_executable(${TARGET_NAME} ${SOURCE_DIR}/main.cpp)

target_include_directories(${TARGET_NAME} PUBLIC ${IMPORT_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDE_DIR})

target_link_directories(${TARGET_NAME} PUBLIC ${IMPORT_STATIC_LIB_DIR})
target_link_directories(${TARGET_NAME} PUBLIC ${IMPORT_DYNAMIC_LIB_DIR})

target_link_libraries(${TARGET_NAME} LINK_PUBLIC ${IMPORT_LIBRARIES})
# CMake can't find 'osgdb_3ds.so' wherever it is.
# Seems like CMake doesn't recognize this file as a library.
#target_link_libraries(${TARGET_NAME} LINK_PUBLIC ${IMPORT_PLUGIN_LIBRARIES})