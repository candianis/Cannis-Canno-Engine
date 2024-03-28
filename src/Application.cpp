#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/config.h>

#include "Shaders/Shader.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Model/Model.h"

const int screen_width = 1024;
const int screen_height = 768;
const float fieldOfView = 45.0f;
bool firstMouse;
float lastX, lastY;
Camera mainCamera(vec3(0.0f, 0.0f, 3.0f));
vec3 globalLightDirection = vec3(1.2f, 1.0f, 2.0f);

const int modelAmount = 3;

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

using Cannis::Shader;
using glm::vec3;
using glm::mat4;

void init();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
/**/
void processInput(GLFWwindow* window, double delta, Camera* camera);
/**/
void update(double delta, Shader* lighting, Camera* camera, Model* currentModel);
/**/
void render(GLFWwindow* window, Shader* lighting, Model* currentModel);
/**/
void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Cannis Canno Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Allow OpenGL to keep track of the z positions of all vertices 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //
    glEnable(GL_STENCIL_TEST);
    //Each bit is written to the stencil buffer as is. 0x00 so that 
    glStencilMask(0xFF);
    //
    glStencilFunc(GL_EQUAL, 1, 0xFF);

    // Initialize our shader program
    Shader lightingShader("basic_light.vert", "basic_light.frag");
    Shader lightCubeShader("light_cube.vert", "light_cube.frag");
    Shader modelVisualization("model_visual.vert", "model_visual.frag");
    init();

    modelVisualization.use();
    
    Model model("f22.obj", "f22.png", false);

    //Engine loop
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double current = glfwGetTime();
        double delta = current - lastTime;
        lastTime = current;

        processInput(window, delta, &mainCamera);
        update(delta, &modelVisualization, &mainCamera, &model);
        render(window, &modelVisualization, &model);
    }

    //Deallocation of all resources
    lightingShader.~Shader();
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

void update(double delta, Shader* lighting, Camera* camera, Model* currentModel) {
    lighting->use();

    mat4 model = mat4(1.0f);
    model = glm::scale(model, vec3(2.0f, 2.0f, 2.0f));
    float angle = delta;
    model = glm::rotate(model, glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));
    lighting->setMatrix4("model", model);

    //the camera coordinates
    mat4 view = mat4(1.0f);
    view = camera->getViewMatrix();
    lighting->setMatrix4("view", view);

    //We assign the world camera to use projection perspective
    mat4 projection = mat4(1.0f);
    projection = glm::perspective(glm::radians(fieldOfView), float(screen_width / screen_width), 0.1f, 100.0f);
    lighting->setMatrix4("projection", projection);
}

void render(GLFWwindow* window, Shader* lighting, Model* currentModel) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //We clear the zbuffer as the model will change coordinates each cycle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    lighting->use();
    currentModel->draw(*lighting);

    glfwSwapBuffers(window);
    glfwPollEvents();
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