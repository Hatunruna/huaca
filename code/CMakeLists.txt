include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_executable(huaca
  main.cc
  local/GroundManager.cc
  local/Hero.cc
  local/LevelGenerator.cc
  local/ItemHUD.cc
  local/ItemManager.cc
  local/Singletons.cc
  local/SoundManager.cc
  local/Timer.cc
  local/WallManager.cc
  # base
  game/AssetManager.cc
  game/Clock.cc
  game/EventManager.cc
  game/Log.cc
  game/Random.cc
  # graphics
  game/Action.cc
  game/Animation.cc
  game/Camera.cc
  game/Control.cc
  game/Entity.cc
  game/EntityManager.cc
  game/ResourceManager.cc
  game/WindowGeometry.cc
  game/WindowSettings.cc
  # model
  game/Model.cc
  game/ModelManager.cc
)

target_link_libraries(huaca
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${SFML2_LIBRARIES}
)

IF (WIN32)
  add_custom_command(
    TARGET huaca
    POST_BUILD
    COMMAND mkdir ARGS -p "${CMAKE_BINARY_DIR}/huaca-win64-release"
    COMMAND cp ARGS -r "${CMAKE_SOURCE_DIR}/libs-win64/*" "${CMAKE_SOURCE_DIR}/data" "${CMAKE_BINARY_DIR}/code/*.exe" "${CMAKE_BINARY_DIR}/huaca-win64-release"
    COMMAND zip ARGS -9r "${CMAKE_BINARY_DIR}/huaca-win64-release.zip" "huaca-win64-release"
    COMMAND rm ARGS -rf "${CMAKE_BINARY_DIR}/huaca-win64-release"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  )
ELSE(WIN32)
  install(
    TARGETS huaca
    RUNTIME DESTINATION games
  )
ENDIF(WIN32)
