#pragma once

// Forward declaration of GLFWwindow so we don't pollute global scope
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
    };
}