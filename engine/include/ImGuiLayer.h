#pragma once
#include <Layer.h>

struct GLFWwindow;

namespace MyTFTEngine {

    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer(GLFWwindow* window);
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        GLFWwindow* m_WindowHandle;
    };
}