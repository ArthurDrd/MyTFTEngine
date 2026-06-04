#
# Engine
#

# Gather Engine files
file(GLOB_RECURSE ENGINE_HEADERS "include/*.h")
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")

# Include GLAD files directly into the engine compilation
set(GLAD_SRC "${CMAKE_SOURCE_DIR}/externals/glad/src/glad.c")

add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SRC})

# Setup include directories
target_include_directories(engine PUBLIC include)
target_include_directories(engine PRIVATE src)

# Include external dependencies
target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/externals/glad/include")
# GLFW provides its own target, so we just link it
target_link_libraries(engine PUBLIC glfw)