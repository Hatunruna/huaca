cmake_minimum_required(VERSION 2.8)

project(GAME
  LANGUAGES C CXX
)

set(PROJECT_NAME "huaca")
set(PROJECT_VERSION 0.1.0)

IF (WIN32)
  set(DATA_DIR "./data/huaca")
ELSE(WIN32)
  include(GNUInstallDirs)
  set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/games/huaca")
ENDIF(WIN32)


find_package(Threads)
find_package(Boost REQUIRED COMPONENTS filesystem system)

IF (WIN32)
  find_package(SFML 2 REQUIRED system window graphics audio)
  set(SFML2_LIBRARIES ${SFML_LIBRARIES})
  set(SFML2_INCLUDE_DIRS ${SFML_INCLUDE_DIR})
ELSE(WIN32)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)
ENDIF(WIN32)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

add_subdirectory(code)

IF (WIN32)
ELSE(WIN32)
  install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/data/${PROJECT_NAME}"
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
  )
ENDIF(WIN32)

find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file("${CMAKE_SOURCE_DIR}/Doxyfile.cmake" "${CMAKE_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile")
endif(DOXYGEN_FOUND)
