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

IF(LORY_ANDROID)
    IF(LORY_ANDROID_NDK_BIN STREQUAL "")
        FIND_PROGRAM(NDK_BUILD ndk-build)
        SET(LORY_ANDROID_NDK_BIN ${NDK_BUILD})
    ENDIF()
    IF(NOT EXISTS ${LORY_ANDROID_NDK_BIN})
        MESSAGE(FATAL_ERROR "ndk-build not found")
    ENDIF()

    MESSAGE(STATUS "NDK_BIN: ${LORY_ANDROID_NDK_BIN}")
    MESSAGE(STATUS "APP_ABI: ${LORY_ANDROID_APP_ABI}")
    MESSAGE(STATUS "INSTALL_TYPE: ${LORY_ANDROID_INSTALL_TYPE}")

    IF(LORY_ANDROID_INSTALL_TYPE STREQUAL "source")
        CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/android/source.mk.in"
            "${PROJECT_BINARY_DIR}/Android.mk")
        CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/android/source-app.mk.in"
            "${PROJECT_BINARY_DIR}/Application.mk")
        SET(LORY_ANDROID_PREFIX "jni")
        INSTALL(FILES "${PROJECT_BINARY_DIR}/Android.mk" DESTINATION "${LORY_ANDROID_PREFIX}")
        INSTALL(FILES "${PROJECT_BINARY_DIR}/Application.mk" DESTINATION "${LORY_ANDROID_PREFIX}")
        INSTALL(DIRECTORY src/lory DESTINATION "${LORY_ANDROID_PREFIX}")
        INSTALL(FILES android/bridge.c DESTINATION "${LORY_ANDROID_PREFIX}/lory")
        INSTALL(DIRECTORY include/lory DESTINATION "${LORY_ANDROID_PREFIX}/include")

        ADD_CUSTOM_TARGET(clobber
            COMMAND "rm" "-rf"
                "${PROJECT_BINARY_DIR}/Android.mk"
                "${PROJECT_BINARY_DIR}/Application.mk"
                "${PROJECT_BINARY_DIR}/doc"
                "${PROJECT_SOURCE_DIR}/include/lory/definitions.h"
                "${PROJECT_BINARY_DIR}/CMakeFiles"
                "${PROJECT_BINARY_DIR}/CMakeCache.txt"
                "${PROJECT_BINARY_DIR}/Makefile"
                "${PROJECT_BINARY_DIR}/Doxyfile"
                "${PROJECT_BINARY_DIR}/cmake_install.cmake"
                "${PROJECT_BINARY_DIR}/install_manifest.txt")

    ELSE()
        CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/android/shared.mk.in"
            "${PROJECT_BINARY_DIR}/Android.mk")

        IF(EXISTS "${CMAKE_INSTALL_PREFIX}/src/main")
            SET(LORY_ANDROID_PREFIX "src/main/jniLibs")
            SET(LORY_ANDROID_JNILIBS_NAME "jniLibs")
            SET(LORY_ANDROID_JNILIBS_DEST "src/main")
            SET(LORY_ANDROID_SRC_DIR "src/main/java")
        ELSE()
            SET(LORY_ANDROID_PREFIX "libs")
            SET(LORY_ANDROID_JNILIBS_NAME "libs")
            SET(LORY_ANDROID_JNILIBS_DEST ${CMAKE_INSTALL_PREFIX})
            SET(LORY_ANDROID_SRC_DIR "src")
        ENDIF()

        ADD_CUSTOM_TARGET(androidlib ALL
            COMMAND ${LORY_ANDROID_NDK_BIN}
                "NDK_PROJECT_PATH=${PROJECT_BINARY_DIR}"
                "NDK_OUT=${PROJECT_BINARY_DIR}/obj"
                "NDK_LIBS_OUT=${PROJECT_BINARY_DIR}/${LORY_ANDROID_JNILIBS_NAME}"
                "APP_PLATFORM=${LORY_ANDROID_APP_PLATFORM}"
                "APP_BUILD_SCRIPT=${PROJECT_BINARY_DIR}/Android.mk"
                "APP_ABI=${LORY_ANDROID_APP_ABI}"
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            COMMENT "Building android library" VERBATIM)
        INSTALL(FILES "${PROJECT_SOURCE_DIR}/android/Lory.java" DESTINATION "${LORY_ANDROID_SRC_DIR}/jp/faultier/android/lory")
        INSTALL(DIRECTORY "${PROJECT_BINARY_DIR}/${LORY_ANDROID_JNILIBS_NAME}" DESTINATION ${LORY_ANDROID_JNILIBS_DEST})

        ADD_CUSTOM_TARGET(clobber
            COMMAND "rm" "-rf"
                "${PROJECT_BINARY_DIR}/Android.mk"
                "${PROJECT_BINARY_DIR}/obj"
                "${PROJECT_BINARY_DIR}/doc"
                "${PROJECT_BINARY_DIR}/${LORY_ANDROID_JNILIBS_NAME}"
                "${PROJECT_SOURCE_DIR}/include/lory/definitions.h"
                "${PROJECT_BINARY_DIR}/CMakeFiles"
                "${PROJECT_BINARY_DIR}/CMakeCache.txt"
                "${PROJECT_BINARY_DIR}/Makefile"
                "${PROJECT_BINARY_DIR}/Doxyfile"
                "${PROJECT_BINARY_DIR}/cmake_install.cmake"
                "${PROJECT_BINARY_DIR}/install_manifest.txt")
    ENDIF()

    MESSAGE(STATUS "INSTALL_PATH: ${CMAKE_INSTALL_PREFIX}/${LORY_ANDROID_PREFIX}")

ELSE(LORY_ANDROID)

    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unknown-pragmas -std=c99")
    SET(CMAKE_C_FLAGS_RELEASE "-O2")
    SET(CMAKE_C_FLAGS_DEBUG "-g -O0")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -std=c++0x")

    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

    SET(serial ${LORY_VERSION})
    SET(soserial ${LORY_MAJOR_VERSION})

    INCLUDE_DIRECTORIES(include extlib/igloo)

    FILE(GLOB LibSourceFiles src/lory/*.c)
    ADD_LIBRARY(lory SHARED ${LibSourceFiles})
    SET_TARGET_PROPERTIES(lory PROPERTIES VERSION ${serial} SOVERSION ${soserial})

    FIND_PACKAGE(JPEG REQUIRED)
    FILE(GLOB BinSourceFiles src/loryconv/*.c)
    ADD_EXECUTABLE(loryconv ${BinSourceFiles})
    TARGET_LINK_LIBRARIES(loryconv lory m ${JPEG_LIBRARY})

    FILE(GLOB TestSourceFiles t/*.cpp)
    ADD_EXECUTABLE(run_test ${TestSourceFiles} ${LibSourceFiles})
    TARGET_LINK_LIBRARIES(run_test m)
    ADD_CUSTOM_COMMAND(
        TARGET run_test
        POST_BUILD
        COMMAND run_test
        WORKING_DIRECTORY ./bin)

    IF(LORY_USE_OPENMP)
        FIND_PACKAGE(OpenMP)
        IF(OPENMP_FOUND)
            SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
            MESSAGE("${OpenMP_C_FLAGS}")
            MESSAGE("${CMAKE_C_FLAGS}")
        ENDIF()
    ENDIF()

    INSTALL(TARGETS lory DESTINATION lib)
    INSTALL(TARGETS loryconv DESTINATION bin)
    INSTALL(DIRECTORY include/lory DESTINATION include)

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
ENDIF(LORY_ANDROID)
