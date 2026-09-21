#pragma once
#include "Timestep.h"
#include "ImGuiLayer.h"


// Forward declaration of GLFWwindow
struct GLFWwindow;

namespace MyTFTEngine {
    class Application {
    public:
        Application();
        virtual ~Application();

        bool Initialize();
        void Run();
        void Shutdown();

    private:
        bool m_IsRunning;
        GLFWwindow* m_Window = nullptr;

        ImGuiLayer m_ImGuiLayer;
        float m_LastFrameTime = 0.0f;
    };
}