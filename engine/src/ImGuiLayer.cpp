#include "ImGuiLayer.h"
#include "ImGui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace MyTFTEngine {

    ImGuiLayer::ImGuiLayer(GLFWwindow* window): Layer("ImGuiLayer"), m_WindowHandle(window) {}

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnImGuiRender() {
        ImGui::Begin("Engine Profiler");

        float fps = ImGui::GetIO().Framerate;
        float frameTime = 1000.0f / fps;

        static float fpsHistory[50] = { 0 };
        static int historyOffset = 0;
        static float timeAccumulator = 0.0f;

        timeAccumulator += ImGui::GetIO().DeltaTime;

        if (timeAccumulator >= 0.05f) { // Mise à jour fluide du graphe
            fpsHistory[historyOffset] = fps;
            historyOffset = (historyOffset + 1) % 50;
            timeAccumulator = 0.0f;
        }

        ImGui::Text("FPS: %.0f", fps);
        ImGui::Text("Frame Time: %.2f ms", frameTime);

        ImGui::Spacing();
        ImGui::PlotLines("FPS History", fpsHistory, 50, historyOffset, nullptr, 0.0f, 300.0f, ImVec2(0, 50));

        ImGui::Separator();
        ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));

        ImGui::End();
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}