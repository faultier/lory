CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(lory)

SET(CMAKE_BUILD_TYPE release)

SET(LORY_MAJOR_VERSION 0)
SET(LORY_MINOR_VERSION 1)
SET(LORY_PATCH_VERSION 0)
SET(LORY_VERSION
    ${LORY_MAJOR_VERSION}.${LORY_MINOR_VERSION}.${LORY_PATCH_VERSION})
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/definitions.h.in"
    "${PROJECT_SOURCE_DIR}/include/lory/definitions.h")

OPTION(LORY_USE_OPENMP "Enable OpenMP" OFF)
OPTION(LORY_ANDROID "Build for Android" OFF)
SET(LORY_ANDROID_NDK_BIN "" CACHE STRING "Path to ndk-build")
SET(LORY_ANDROID_APP_ABI "all" CACHE STRING "Target android architecture")
SET(LORY_ANDROID_APP_PLATFORM "android-8" CACHE STRING "Target android platform, required android-8 or later.")
SET(LORY_ANDROID_INSTALL_TYPE "shared" CACHE STRING "Install type")

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    CONFIGURE_FILE(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
    ADD_CUSTOM_TARGET(doc
        ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
ENDIF(DOXYGEN_FOUND)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unknown-pragmas -std=c99")
SET(CMAKE_C_FLAGS_RELEASE "-O2")
SET(CMAKE_C_FLAGS_DEBUG "-g -O0")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -std=c++0x")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

SET(serial ${LORY_VERSION})
SET(soserial ${LORY_MAJOR_VERSION})

FILE(GLOB LibSourceFiles src/lory/*.c)

IF(ANDROID)
    INCLUDE_DIRECTORIES(include)
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lm -llog -ljnigraphics")

    ADD_LIBRARY(lory SHARED ${LibSourceFiles} android/bridge.c)
    INSTALL(TARGETS lory DESTINATION ${ANDROID_SO_PREFIX})
    INSTALL(FILES android/Lory.java DESTINATION ${ANDROID_SRC_PREFIX}/jp/faultier/android/lory)
ELSE()
    INCLUDE_DIRECTORIES(include extlib/igloo)

    ADD_LIBRARY(lory SHARED ${LibSourceFiles})
    SET_TARGET_PROPERTIES(lory PROPERTIES VERSION ${serial} SOVERSION ${soserial})
    INSTALL(TARGETS lory DESTINATION lib)
    INSTALL(DIRECTORY include/lory DESTINATION include)

    FIND_PACKAGE(JPEG REQUIRED)
    FILE(GLOB BinSourceFiles src/loryconv/*.c)
    ADD_EXECUTABLE(loryconv ${BinSourceFiles})
    ADD_DEPENDENCIES(loryconv lory)
    TARGET_LINK_LIBRARIES(loryconv lory m ${JPEG_LIBRARY})
    INSTALL(TARGETS loryconv DESTINATION bin)

    FILE(GLOB TestSourceFiles t/*.cpp t/*.c)
    ADD_EXECUTABLE(run_test ${TestSourceFiles} ${LibSourceFiles})
    TARGET_LINK_LIBRARIES(run_test m)
    ADD_CUSTOM_COMMAND(
        TARGET run_test
        POST_BUILD
        COMMAND run_test
        WORKING_DIRECTORY ./bin)
ENDIF()

ADD_CUSTOM_TARGET(clobber
    COMMAND "rm" "-rf"
    "${PROJECT_BINARY_DIR}/bin"
    "${PROJECT_BINARY_DIR}/lib"
    "${PROJECT_BINARY_DIR}/doc"
    "${PROJECT_BINARY_DIR}/include/lory/definitions.h"
    "${PROJECT_BINARY_DIR}/CMakeFiles"
    "${PROJECT_BINARY_DIR}/CMakeCache.txt"
    "${PROJECT_BINARY_DIR}/Makefile"
    "${PROJECT_BINARY_DIR}/Doxyfile"
    "${PROJECT_BINARY_DIR}/cmake_install.cmake"
    "${PROJECT_BINARY_DIR}/install_manifest.txt")
