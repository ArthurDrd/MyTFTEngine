#
# Game
#

# Collect your game source files
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/engine/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Tell CMake to build an actual executable (.exe)
add_executable(TFTGame ${GAME_SOURCES})

# Link your engine static library to the executable
target_link_libraries(TFTGame PRIVATE engine)