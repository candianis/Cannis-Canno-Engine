#include "InputManager.h"

#include <glad/glad.h>

GLFWwindow* InputManager::m_window;
shared_ptr<Camera> InputManager::s_camera;

bool InputManager::s_firstMouse;
float InputManager::lastX;
float InputManager::lastY;

InputManager::InputManager() {
    
}

void InputManager::start(shared_ptr<Camera> p_camera) {
    s_camera = p_camera;
}

void InputManager::update(float delta) {

}

void InputManager::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (s_firstMouse) {
        lastX = xpos;
        lastY = ypos;
        s_firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    s_camera->rotateCamera(xoffset, yoffset);
}