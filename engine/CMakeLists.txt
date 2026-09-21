#
# Engine
#

# Headers
set(ENGINE_HEADERS
    "include/Engine.h"
    "include/Shader.h"
    "include/Buffer.h"
    "include/VertexArray.h"
    "include/Renderer.h"
    "include/Timestep.h"
    "include/ImGuiLayer.h"
)

# Sources
set(ENGINE_SOURCES
    "src/Engine.cpp"
    "src/Shader.cpp"
    "src/Buffer.cpp"
    "src/VertexArray.cpp"
    "src/Renderer.cpp"
    "src/ImGuiLayer.cpp"
)

# GLAD source file (since it's a single C file)
set(GLAD_SRC "${CMAKE_SOURCE_DIR}/externals/glad/src/glad.c")

# IMGUI source file
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/externals/imgui")
set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

# Create a static library target for the engine
add_library(engine STATIC 
    ${ENGINE_SOURCES} 
    ${ENGINE_HEADERS} 
    ${GLAD_SRC}
    ${IMGUI_SOURCES}
)

# Setup include directories
target_include_directories(engine PUBLIC include)
target_include_directories(engine PRIVATE src)

# Include external dependencies
target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/externals/glad/include")
target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/externals/glm")

# Include IMGUI directories
target_include_directories(engine PUBLIC "${IMGUI_DIR}")
target_include_directories(engine PUBLIC "${IMGUI_DIR}/backends")

# GLFW provides its own target, so we just link it
target_link_libraries(engine PUBLIC glfw)