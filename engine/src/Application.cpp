#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Renderer.h>


namespace MyTFTEngine {
    Application* Application::s_Instance = nullptr;
    
   Application::Application() : m_IsRunning(false), m_Window(nullptr) {
        // Assertion pour vérifier qu'on ne crée pas deux Application
        if (!s_Instance) {
            s_Instance = this;
        } else {
            std::cerr << "[Engine Error] Application already exists!" << std::endl;
        }
    }

    Application::~Application() {
        s_Instance = nullptr;
    }

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

        m_ImGuiLayer = new ImGuiLayer(m_Window);
        PushOverlay(m_ImGuiLayer);

        m_IsRunning = true;
        return true;
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
    }

    glm::vec2 Application::GetWindowSize() const {
        int width, height;
        glfwGetWindowSize(m_Window, &width, &height);
        return { static_cast<float>(width), static_cast<float>(height) };
    }

    void Application::Run() {
        std::cout << "[Engine] Entering Main Loop..." << std::endl;
       
        while (m_IsRunning && !glfwWindowShouldClose(m_Window)) {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            Renderer::Clear(0.12f, 0.15f, 0.22f, 1.0f);

            for (Layer* layer : m_LayerStack) {
                layer->OnRender();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }

    void Application::Shutdown() {
        std::cout << "[Engine] Shutting down..." << std::endl;
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
    }
}