CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(lory)

SET(CMAKE_BUILD_TYPE release)

SET(LORY_MAJOR_VERSION 0)
SET(LORY_MINOR_VERSION 1)
SET(LORY_PATCH_VERSION 0)
SET(LORY_VERSION
    ${LORY_MAJOR_VERSION}.${LORY_MINOR_VERSION}.${LORY_PATCH_VERSION})
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/src/lory/version.h.in"
    "${PROJECT_BINARY_DIR}/include/lory/version.h")

OPTION(LORY_ANDROID "Build for Android" OFF)
OPTION(LORY_TEST "Run tests using igloo" OFF)
SET(LORY_ANDROID_NDK_BIN "" CACHE STRING "Path to ndk-build")
SET(LORY_ANDROID_APP_ABI "all" CACHE STRING "Target android architecture")
SET(LORY_ANDROID_PREFIX "jni/extlib" CACHE STRING "Install prefix")

IF(LORY_ANDROID)

    IF(LORY_ANDROID_NDK_BIN STREQUAL "")
        FIND_PROGRAM(NDK_BUILD ndk-build)
        SET(LORY_ANDROID_NDK_BIN ${NDK_BUILD})
    ENDIF()
    IF(NOT EXISTS ${LORY_ANDROID_NDK_BIN})
        MESSAGE(FATAL_ERROR "ndk-build not found")
    ENDIF()
    ADD_CUSTOM_TARGET(lory ALL
        COMMAND ${LORY_ANDROID_NDK_BIN}
            "NDK_PROJECT_PATH=${PROJECT_SOURCE_DIR}"
            "NDK_OUT=${PROJECT_BINARY_DIR}/out"
            "APP_BUILD_SCRIPT=${PROJECT_SOURCE_DIR}/Android.mk"
            "APP_ABI=${LORY_ANDROID_APP_ABI}"
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Building android library" VERBATIM)
    MESSAGE(STATUS "${LORY_ANDROID_APP_ABI}")
    IF ("${LORY_ANDROID_APP_ABI}" STREQUAL "all")
        INSTALL(FILES "${PROJECT_BINARY_DIR}/out/local/armeabi/liblory.a" DESTINATION "${LORY_ANDROID_PREFIX}/lory/armeabi")
        INSTALL(FILES "${PROJECT_BINARY_DIR}/out/local/armeabi-v7a/liblory.a" DESTINATION "${LORY_ANDROID_PREFIX}/lory/armeabi-v7a")
        INSTALL(FILES "${PROJECT_BINARY_DIR}/out/local/mips/liblory.a" DESTINATION "${LORY_ANDROID_PREFIX}/lory/mips")
        INSTALL(FILES "${PROJECT_BINARY_DIR}/out/local/x86/liblory.a" DESTINATION "${LORY_ANDROID_PREFIX}/lory/x86")
    ELSE()
        INSTALL(FILES "${PROJECT_BINARY_DIR}/out/local/${LORY_ANDROID_APP_ABI}/liblory.a" DESTINATION "${LORY_ANDROID_PREFIX}/lory/${LORY_ANDROID_APP_ABI}")
    ENDIF()
    INSTALL(DIRECTORY include/lory DESTINATION "${LORY_ANDROID_PREFIX}/include")

ELSE(LORY_ANDROID)

    SET(CMAKE_C_FLAGS "-Wall -std=c99")
    SET(CMAKE_C_FLAGS_RELEASE "-O2")
    SET(CMAKE_C_FLAGS_DEBUG "-g -O0")
    SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x")

    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

    SET(serial ${LORY_VERSION})
    SET(soserial ${LORY_MAJOR_VERSION})

    INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include" include extlib/igloo)

    FILE(GLOB LibSourceFiles src/lory/*.c)
    ADD_LIBRARY(lory SHARED ${LibSourceFiles})
    SET_TARGET_PROPERTIES(lory PROPERTIES VERSION ${serial} SOVERSION ${soserial})

    FIND_PACKAGE(JPEG REQUIRED)
    FILE(GLOB BinSourceFiles src/loryconv/*.c)
    ADD_EXECUTABLE(loryconv ${BinSourceFiles})
    TARGET_LINK_LIBRARIES(loryconv lory m ${JPEG_LIBRARY})

    FIND_PACKAGE(Doxygen)
    IF(DOXYGEN_FOUND)
        CONFIGURE_FILE(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
        ADD_CUSTOM_TARGET(doc
            ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
    ENDIF(DOXYGEN_FOUND)

    IF(LORY_TEST)
        FILE(GLOB TestSourceFiles t/*.cpp)
        ADD_EXECUTABLE(run_test ${TestSourceFiles} ${LibSourceFiles})
        TARGET_LINK_LIBRARIES(run_test m)
        ADD_CUSTOM_COMMAND(
            TARGET run_test
            POST_BUILD
            COMMAND run_test
            WORKING_DIRECTORY ./bin)
    ENDIF(LORY_TEST)

    INSTALL(TARGETS lory DESTINATION lib)
    INSTALL(TARGETS loryconv DESTINATION bin)
    INSTALL(DIRECTORY include/lory DESTINATION include)
    INSTALL(FILES "${PROJECT_BINARY_DIR}/include/lory/version.h" DESTINATION "include/lory")

ENDIF(LORY_ANDROID)
