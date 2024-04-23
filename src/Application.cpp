#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/config.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Model/Model.h"

#include "Managers/GuiManager/GuiManager.h"
#include "Managers/ShaderManager/ShaderManager.h"

const int screen_width = 1024;
const int screen_height = 768;
const float fieldOfView = 45.0f;
bool firstMouse;
float lastX, lastY;
Camera mainCamera(vec3(0.0f, 0.0f, 3.0f));
vec3 globalLightDirection = vec3(1.2f, 1.0f, 2.0f);
glm::vec3 lightPos(0.0f, 2.0f, 0.0f);

ShaderSlot::ShaderSlot shaderSlot = ShaderSlot::Blinn_Phong;

const int modelAmount = 3;

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

using Cannis::Shader;
using Cannis::GuiManager;
using Cannis::ShaderManager;
using glm::vec3;
using glm::mat4;

// @brief 
void init();
// @brief
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
// @brief 
void processInput(GLFWwindow* window, double delta, Camera* camera);
// @brief 
void update(double delta, std::shared_ptr<ShaderManager> p_shaderManager, Camera* camera, Model* currentModel);
// @brief
void render(GLFWwindow* window, std::shared_ptr<ShaderManager> p_shaderManager, Model* currentModel, GuiManager* guiManager);
// @brief 
void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Cannis Canno Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // Activate vsync
    //glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GuiManager guiManager(window, 800, 600);

    //Allow OpenGL to keep track of the z positions of all vertices 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_MULTISAMPLE);

    // Initialize our shader program
    std::shared_ptr<ShaderManager> shaderManager = std::make_shared<ShaderManager>();

    init();

    shaderManager->useShader(ShaderSlot::Model_Visualization);
    
    Model model("f22.obj", "f22.png", false);

    double lastTime = glfwGetTime();
    double currentTime = 0.0;
    double delta = 0.0;
    size_t counter = 0;

    //Engine loop
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        ++counter;
        if (delta > 1.0f / 30.0f) {
            double fps = (1.0 / delta) * counter;
            double ms = (delta / counter) * 1000;

            //std::cout << "FPS: " << fps << " | " << ms << " ms | Counter: " << counter << std::endl;

            lastTime = currentTime;
            counter = 0;
        }
        
        processInput(window, delta, &mainCamera);
        update(delta, shaderManager, &mainCamera, &model);
        render(window, shaderManager, &model, &guiManager);
    }

    //Deallocation of all resources
    shaderManager->clean();
    model.clean();
    glfwTerminate();

    return 0;
}

void init() {

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, double delta, Camera* camera) {
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveCamera(FORWARD, delta);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveCamera(BACKWARD, delta);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveCamera(RIGHT, delta);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveCamera(LEFT, delta);
}

void update(double delta, std::shared_ptr<ShaderManager> p_shaderManager, Camera* camera, Model* currentModel) {
    p_shaderManager->useShader(shaderSlot);

    mat4 model = mat4(1.0f);
    model = glm::scale(model, vec3(2.0f, 2.0f, 2.0f));
    float angle = delta;
    model = glm::rotate(model, glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));
    p_shaderManager->setMatrix4(shaderSlot, "model", model);

    //the camera coordinates
    mat4 view = mat4(1.0f);
    view = camera->getViewMatrix();
    p_shaderManager->setMatrix4(shaderSlot, "view", view);

    //We assign the world camera to use projection perspective
    mat4 projection = mat4(1.0f);
    projection = glm::perspective(glm::radians(fieldOfView), float(screen_width / screen_width), 0.1f, 100.0f);
    p_shaderManager->setMatrix4(shaderSlot, "projection", projection);

    p_shaderManager->setVec3(shaderSlot, "viewPos", camera->position);
    p_shaderManager->setVec3(shaderSlot, "lightPos", lightPos);
    p_shaderManager->setInt(shaderSlot, "blinn", 1);


    //p_shaderManager->setFloat(shaderSlot, "time", glfwGetTime());
}

void render(GLFWwindow* window, std::shared_ptr<ShaderManager> p_shaderManager, Model* currentModel, GuiManager* guiManager) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //We clear the zbuffer as the model will change coordinates each cycle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    guiManager->update();

    p_shaderManager->useShader(shaderSlot);
    currentModel->draw(p_shaderManager->getShader(shaderSlot));
    
    guiManager->lateUpdate();

    glfwSwapBuffers(window);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    mainCamera.rotateCamera(xoffset, yoffset);
}