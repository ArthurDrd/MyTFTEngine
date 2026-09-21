#pragma once

struct GLFWwindow;

namespace MyTFTEngine {

    class ImGuiLayer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void Init(GLFWwindow* window);
        void Shutdown();

        // Encadrement du rendu GUI
        void Begin();
        void End();
    };
}