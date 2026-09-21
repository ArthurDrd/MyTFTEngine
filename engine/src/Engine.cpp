#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>
#include <VertexArray.h>
#include <Buffer.h>
#include <Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>


namespace MyTFTEngine {
    Application::Application() : m_IsRunning(false), m_Window(nullptr) {}
    Application::~Application() {}

    bool Application::Initialize() {
        std::cout << "[Engine] Initializing subsystems..." << std::endl;

        if (!glfwInit()) {
            std::cerr << "[Engine] Failed to initialize GLFW!" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create the window
        m_Window = glfwCreateWindow(1280, 720, "Scuffed TFT", nullptr, nullptr);
        if (!m_Window) {
            std::cerr << "[Engine] Failed to create GLFW window!" << std::endl;
            glfwTerminate();
            return false;
        }

        // Make the window's context current
        glfwMakeContextCurrent(m_Window);

        // Initialize GLAD function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "[Engine] Failed to initialize GLAD!" << std::endl;
            return false;
        }

        // Initialise notre Renderer tout neuf !
        Renderer::Init();

        std::cout << "[Engine] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        m_ImGuiLayer.Init(m_Window);

        m_IsRunning = true;
        return true;
    }

    void Application::Run() {
        std::cout << "[Engine] Entering Main Loop..." << std::endl;

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  // Bas Gauche
             0.5f, -0.5f, 0.0f,  // Bas Droite
             0.5f,  0.5f, 0.0f,  // Haut Droite
            -0.5f,  0.5f, 0.0f   // Haut Gauche
        };

        unsigned int indices[] = {
            0, 1, 2,  // Premier triangle
            2, 3, 0   // Deuxième triangle
        };

        auto defaultShader = std::make_shared<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
        auto va = std::make_shared<VertexArray>();
        auto vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        auto ib = std::make_shared<IndexBuffer>(indices, 6);
        va->AddVertexBuffer(vb);
        va->SetIndexBuffer(ib);

        while (m_IsRunning && !glfwWindowShouldClose(m_Window)) {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            
            Renderer::Clear(0.12f, 0.15f, 0.22f, 1.0f);

            defaultShader->Bind();

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

            glm::mat4 view = glm::lookAt(
                glm::vec3(0.0f, 3.0f, 5.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );

            glm::mat4 viewProjection = projection * view;
            defaultShader->SetMat4("u_ViewProjection", viewProjection);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            defaultShader->SetMat4("u_Model", model);

            Renderer::Draw(va, defaultShader);

            // IMGUI
            m_ImGuiLayer.Begin();

            ImGui::Begin("Engine Profiler");

            static float frameCount = 0.0f;
            static float timeAccumulator = 0.0f;
            static float displayedFPS = 0.0f;
            static float displayedFrameTime = 0.0f;

            static float fpsHistory[50] = { 0 };
            static int historyOffset = 0;

            frameCount++;
            timeAccumulator += timestep.GetSeconds();

            if (timeAccumulator >= 0.2f) {
                displayedFPS = frameCount / timeAccumulator;
                displayedFrameTime = (timeAccumulator / frameCount) * 1000.0f;

                // Mise à jour du tableau pour le graphique
                fpsHistory[historyOffset] = displayedFPS;
                historyOffset = (historyOffset + 1) % 50;

                // Réinitialisation des compteurs
                frameCount = 0.0f;
                timeAccumulator = 0.0f;
            }

            ImGui::Text("FPS: %.0f", displayedFPS);
            ImGui::Text("Frame Time: %.2f ms", displayedFrameTime);

            ImGui::Spacing();

            ImGui::PlotLines("FPS History", fpsHistory, 50, historyOffset, nullptr, 0.0f, 300.0f, ImVec2(0, 50));
            
            ImGui::Separator();
            ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));

            ImGui::End();
            m_ImGuiLayer.End();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }

    void Application::Shutdown() {
        std::cout << "[Engine] Shutting down..." << std::endl;
        m_ImGuiLayer.Shutdown();
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
    }
}