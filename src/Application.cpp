#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders/Shader.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"

const int screen_width = 1024;
const int screen_height = 768;
const float fieldOfView = 45.0f;
bool firstMouse;
float lastX, lastY;
Camera mainCamera(vec3(0.0f, 0.0f, 3.0f));
vec3 globalLightDirection = vec3(1.2f, 1.0f, 2.0f);

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

using glm::vec3;
using glm::mat4;

void init();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
/**/
void processInput(GLFWwindow* window, double delta, Camera* camera);
/**/
void update(double delta, Shader* lighting, Shader* lightCubeShader, Camera* camera, Texture* texture, Texture* specular, Texture* emission);
/**/
void render(GLFWwindow* window, Shader* lighting, Shader* lightCube, const unsigned int cubeVAO, const unsigned int lightCubeVAO);
/**/
void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Cannis Canno Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Allow OpenGL to keep track of the z positions of all vertices 
    glEnable(GL_DEPTH_TEST);

    // Initialize our shader program
    Shader lightingShader("./src/Shaders/Vertex/basic_light.vert", "./src/Shaders/Fragment/basic_light.frag");
    Shader lightCubeShader("./src/Shaders/Vertex/light_cube.vert", "./src/Shaders/Fragment/light_cube.frag");
    init();

    //Simple rectangle. Each line specifies the value of a single vertex
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attribute(s).
    glBindVertexArray(cubeVAO);

    //Size of a single vertex value according to the array of vertices
    int vertexSize = 8;

    //Set the layout 0 with the vertices' positions. 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);

    //normals for each vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));

    //Texture coordinates 
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(6 * sizeof(float)));    

    // Unbind the VBO and VAO so that unwanted changes cannot be done
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //float positions of each vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);

    lightingShader.use();

    //Set the light's values as uniforms
       // directional light
    lightingShader.setVec3("dirLight.direction", globalLightDirection);
    lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    // point light 1
    lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[0].constant", 1.0f);
    lightingShader.setFloat("pointLights[0].linear", 0.09f);
    lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[1].constant", 1.0f);
    lightingShader.setFloat("pointLights[1].linear", 0.09f);
    lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[2].constant", 1.0f);
    lightingShader.setFloat("pointLights[2].linear", 0.09f);
    lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
    lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[3].constant", 1.0f);
    lightingShader.setFloat("pointLights[3].linear", 0.09f);
    lightingShader.setFloat("pointLights[3].quadratic", 0.032f);

    //Textures 
    Texture woodenCrateTexture("wooden_container.png");
    lightingShader.setInt("material.diffuse", 0);

    Texture specularMap("wooden_container_specular.png");
    lightingShader.setInt("material.specular", 1);

    Texture emissionMap("wooden_container_emission.jpg", GL_CLAMP_TO_BORDER);
    lightingShader.setInt("material.emission", 2);

    //Set the material's values as uniforms
    lightingShader.setFloat("material.shininess", 32.0f);

    //Engine loop
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double current = glfwGetTime();
        double delta = current - lastTime;

        processInput(window, delta, &mainCamera);
        update(delta, &lightingShader, &lightCubeShader, &mainCamera, &woodenCrateTexture, &specularMap, &emissionMap);
        render(window, &lightingShader, &lightCubeShader, cubeVAO, lightCubeVAO);

        lastTime = current;
    }

    //Deallocation of all resources
    woodenCrateTexture.cleanUp();
    specularMap.cleanUp();
    emissionMap.cleanUp();
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);
    lightingShader.~Shader();
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

void update(double delta, Shader* lighting, Shader* lightCube, Camera* camera, Texture* texture, Texture* specular, Texture* emission) {
    lighting->use();
    lighting->setVec3("viewPos", camera->position);
    lighting->setVec3("dirLight.position", globalLightDirection);

    mat4 model = mat4(1.0f);
    lighting->setMatrix4("model", model);

    //the camera coordinates
    mat4 view = mat4(1.0f);
    view = camera->getViewMatrix();
    lighting->setMatrix4("view", view);

    //We assign the world camera to use projection perspective
    mat4 projection = mat4(1.0f);
    projection = glm::perspective(glm::radians(fieldOfView), float(screen_width / screen_width), 0.1f, 100.0f);
    lighting->setMatrix4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    glActiveTexture(GL_TEXTURE1);
    specular->bind();

    glActiveTexture(GL_TEXTURE2);
    emission->bind();

    lightCube->use();
    lightCube->setMatrix4("projection", projection);
    lightCube->setMatrix4("view", view);
}

void render(GLFWwindow* window, Shader* lighting, Shader* lightCube, const unsigned int cubeVAO, const unsigned int lightCubeVAO) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //We clear the zbuffer as the model will change coordinates each cycle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting->use();
    glBindVertexArray(cubeVAO);
    for (size_t i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        lighting->setMatrix4("model", model);
        glm::mat3 inverse = glm::transpose(glm::inverse(model));
        lighting->setMatrix3("inverseModel", inverse);

        glDrawArrays(GL_TRIANGLES, 0, 36);  
    }

    lightCube->use();
    glBindVertexArray(lightCubeVAO);
    for (size_t i = 0; i < 4; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, vec3(0.2f));
        lightCube->setMatrix4("model", model);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
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