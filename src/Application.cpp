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
Camera mainCamera(vec3(0.0f, 0.0f, -5.0f));
vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);

using glm::vec3;
using glm::mat4;

void init();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
/**/
void processInput(GLFWwindow* window, double delta, Camera* camera);
/**/
void update(double delta, Shader* lighting, Shader* lightCube, Camera* camera, Texture* texture, Texture* specular, Texture* emission);
/**/
void render(GLFWwindow* window, Shader* lighting, Shader* lightCube, const unsigned int cubeVAO, const unsigned int lightCubeVAO);
/**/
void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);


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
    glfwSetCursorPosCallback(window, MouseCallback);

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

    //Scene colors
    vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    lightingShader.Use();

    //Set the material's values as uniforms
    lightingShader.SetVec3("material.specular", vec3(0.5f, 0.5f, 0.5f));
    lightingShader.SetFloat("material.shininess", 64.0f);

    //Set the light's values as uniforms
    lightingShader.SetVec3("light.position", lightPos);
    lightingShader.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

    //Textures 
    Texture woodenCrateTexture("wooden_container.png");
    lightingShader.SetInt("material.diffuse", 0);

    Texture specularMap("wooden_container_specular.png");
    lightingShader.SetInt("material.specular", 1);

    Texture emissionMap("wooden_container_emission.jpg", GL_CLAMP_TO_BORDER);
    lightingShader.SetInt("material.emission", 2);

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
    woodenCrateTexture.Delete();
    specularMap.Delete();
    emissionMap.Delete();
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
        camera->MoveCamera(FORWARD, delta);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->MoveCamera(BACKWARD, delta);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->MoveCamera(RIGHT, delta);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->MoveCamera(LEFT, delta);
}

void update(double delta, Shader* lighting, Shader* lightCube, Camera* camera, Texture* texture, Texture* specular, Texture* emission) {
    mat4 model = mat4(1.0f);

    //Transpose and inverse the model so that it is calculated only once and not for each vertex
    glm::mat3 inverse = glm::transpose(glm::inverse(model));

    //the camera coordinates
    mat4 view = mat4(1.0f);
    view = camera->GetViewMatrix();

    //We assign the world camera to use projection perspective
    mat4 projection = mat4(1.0f);
    projection = glm::perspective(glm::radians(fieldOfView), float(screen_width / screen_width), 0.1f, 100.0f);

    lighting->Use();
    lighting->SetVec3("viewPos", camera->position);

    lighting->SetMatrix4("model", model);
    lighting->SetMatrix3("inverseModel", inverse);

    lighting->SetMatrix4("view", view);
    lighting->SetMatrix4("projection", projection);

    float lightX = 2.0f * sin(glfwGetTime());
    float lightY = -0.3f;
    float lightZ = 1.5f * cos(glfwGetTime());
    lightPos = glm::vec3(lightX, lightY, lightZ);

    // send light position to lightingShader
    lighting->SetVec3("light.position", lightPos);

    lightCube->Use();
    lightCube->SetMatrix4("projection", projection);
    lightCube->SetMatrix4("view", view);


    model = glm::translate(model, lightPos);
    model = glm::scale(model, vec3(0.2f));
    lightCube->SetMatrix4("model", model);

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    glActiveTexture(GL_TEXTURE1);
    specular->Bind();

    glActiveTexture(GL_TEXTURE2);
    emission->Bind();
}

void render(GLFWwindow* window, Shader* lighting, Shader* lightCube, const unsigned int cubeVAO, const unsigned int lightCubeVAO) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //We clear the zbuffer as the model will change coordinates each cycle
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting->Use();
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    lightCube->Use();
    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
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

    mainCamera.RotateCamera(xoffset, yoffset);
}