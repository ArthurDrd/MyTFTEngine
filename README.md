# MyTFTEngine (Custom 2D/3D Game Engine & Auto-Battler)

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OpenGL](https://img.shields.io/badge/OpenGL-4.5-green.svg)
![Platform](https://img.shields.io/badge/Platform-Cross--Platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

A lightweight, custom game engine built from scratch in C++17 and OpenGL, tailored specifically to run a custom clone of *Teamfight Tactics*. 

This project uses a strict decoupled architecture, separating the underlying engine core from the game logic to maximize framework reusability and clean separation of concerns.

---

## ✨ Current Features

- **Hexagonal Grid System:** Point-topped hex math, coordinate generation, and spatial layout tailored for auto-battler arenas.
- **Modern Shader-Based Rendering:** Procedural tile outlines computed directly in fragment shaders with smooth antialiasing (`smoothstep`), replacing obsolete fixed-pipeline lines.
- **3D Raycasting & Mouse Picking:** Screen-to-world ray generation, unprojection via camera matrices, and ray-plane intersection ($Y=0$) for real-time tile hovering.
- **Layer-Based Architecture:** Event and update loops managed via a robust `LayerStack` system (separating game layers from UI/ImGui overlays).
- **Cross-Platform Build System:** Modern target-based CMake with external dependency management via Git submodules.

---

## 🛠️ Architecture Overview

The project is structured into three strictly bounded layers:

- **`engine/`**: Core engine subsystem (Windowing, OpenGL rendering abstractions, Camera, Raycaster, Input handling, Delta-timing). Completely decoupled from game logic.
- **`game/`**: Game-specific mechanics (TFT Board grid, Hex math, Champion states, custom game layers). Developed using the `MyTFTEngine` namespace.
- **`externals/`**: Third-party libraries managed via modern CMake (`GLFW`, `GLAD`, `GLM`, `IMGUI`).

---

## 🚀 Quick Start / How to Build

This project uses modern target-based CMake and is completely cross-platform.

### Prerequisites
* A C++17 compatible compiler (MSVC, GCC, or Clang)
* CMake (Version 3.15 or higher)

### Cloning the Repository
Because this project utilizes Git Submodules for dependencies, ensure you clone recursively:
```bash
git clone --recursive https://github.com/ArthurDrd/MyTFTEngine
cd MyTFTEngine
```

### Building the Project

#### Via Command Line
From the root directory of the project, run the following commands to generate build files and compile the executable:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
Once compilation finishes, your executable will be located in the build/game/ folder as TFTGame.exe (or TFTGame on Mac/Linux).

#### Via an IDE
1. Open your IDE and select Open Folder / Open Project, choosing the root directory containing the main CMakeLists.txt.

2. Allow your IDE's built-in CMake tool to finish indexing and generating its configuration cache.

3. CRITICAL STEP: Locate your IDE's target selector dropdown (typically near the top "Run/Play" button). Ensure the active target is set to TFTGame. Do not run the engine target directly, as it compiles into a static library (.lib/.a) rather than a launchable program.

4. Click Run or Debug.