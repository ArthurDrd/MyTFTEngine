#
# Engine
#

# Headers
set(ENGINE_HEADERS
    "include/Engine.h"
    "include/Shader.h"
    "include/Buffer.h"
    "include/VertexArray.h"
)

# Sources
set(ENGINE_SOURCES
    "src/Engine.cpp"
    "src/Shader.cpp"
    "src/Buffer.cpp"
    "src/VertexArray.cpp"
)

# GLAD source file (since it's a single C file)
set(GLAD_SRC "${CMAKE_SOURCE_DIR}/externals/glad/src/glad.c")

# Create a static library target for the engine
add_library(engine STATIC 
    ${ENGINE_SOURCES} 
    ${ENGINE_HEADERS} 
    ${GLAD_SRC}
)

# Setup include directories
target_include_directories(engine PUBLIC include)
target_include_directories(engine PRIVATE src)

# Include external dependencies
target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/externals/glad/include")

# GLFW provides its own target, so we just link it
target_link_libraries(engine PUBLIC glfw)