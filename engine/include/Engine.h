#pragma once
#include "Timestep.h"
#include "ImGuiLayer.h"
#include "Layer.h"
#include "LayerStack.h"

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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

    private:
        bool m_IsRunning;
        GLFWwindow* m_Window = nullptr;

        float m_LastFrameTime = 0.0f;

        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer = nullptr;
    };
}