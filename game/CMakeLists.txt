#
# Game
#

# Collect your game source files
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

# Tell CMake to build an actual executable (.exe)
add_executable(TFTGame ${GAME_SOURCES})

# Link your engine static library to the executable
target_link_libraries(TFTGame PRIVATE engine)