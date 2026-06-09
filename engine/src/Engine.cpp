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