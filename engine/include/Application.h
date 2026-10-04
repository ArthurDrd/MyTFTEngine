#pragma once
#include "Timestep.h"
#include "ImGuiLayer.h"
#include "Layer.h"
#include "LayerStack.h"
#include <glm/glm.hpp>

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

        inline GLFWwindow* GetNativeWindow() const { return m_Window; }
        inline static Application& Get() { return *s_Instance; }
        glm::vec2 GetWindowSize() const;

    private:
        static Application* s_Instance;

        bool m_IsRunning;
        GLFWwindow* m_Window = nullptr;

        float m_LastFrameTime = 0.0f;

        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer = nullptr;
    };
}