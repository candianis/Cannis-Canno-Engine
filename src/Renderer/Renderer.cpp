#include "Renderer.h"
#include "../Managers/InputManager/InputManager.h"

#include <iostream>


Renderer::Renderer(int p_screenWidth, int p_screenHeight, float p_fieldOfView) : screenWidth(p_screenWidth), screenHeight(p_screenHeight), fieldOfView(p_fieldOfView), currentShader(ShaderSlot::Blinn_Phong) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_window = glfwCreateWindow(screenWidth, screenHeight, "Cannis Canno Engine", NULL, NULL);
    if (m_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallbackR);
    glfwSetCursorPosCallback(m_window, InputManager::mouseCallback);

    mainCamera = std::make_unique<Camera>();
}

void Renderer::init() {
    //Allow OpenGL to keep track of the z positions of all vertices 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_MULTISAMPLE);
}

void Renderer::update() {

}

void Renderer::clean() {
    glfwTerminate();
}

GLFWwindow* Renderer::getWindow() {
    return m_window;
}

void Renderer::enableVSync(bool p_activateVSync = true) {
    if (p_activateVSync) {
        glfwSwapInterval(1);
        return;
    }

    glfwSwapInterval(0);
}

void Renderer::framebufferSizeCallbackR(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}