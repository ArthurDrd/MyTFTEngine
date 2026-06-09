#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

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

        std::cout << "[Engine] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        m_IsRunning = true;
        return true;
    }

    void Application::Run() {
        std::cout << "[Engine] Entering Main Loop..." << std::endl;


        Shader defaultShader("assets/shaders/default.vert", "assets/shaders/default.frag");

        // Keep running until the window is closed or m_IsRunning is flagged false
        while (m_IsRunning && !glfwWindowShouldClose(m_Window)) {

            glClearColor(0.12f, 0.15f, 0.22f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            defaultShader.Bind();

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