#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shaders/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRING
#define STBI_FAILURE_USERMSG
#include "stb/stb_image.h"

void init();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void update(double delta);
void render(GLFWwindow* window, Shader* shader, unsigned int texture, unsigned int* VAO, unsigned int* EBO);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cannis Canno Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // Initialize our shader program
    Shader triangleShader("./src/Shaders/Vertex/test.vert", "./src/Shaders/Fragment/test.frag");
    init();

    //Simple rectangle. Each line specifies the value of a single vertex
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int EBO, VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Size of a single vertex value according to the array of vertices
    int vertexSize = 8;

    //Set the layout 0 with the vertices' positions. 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Set the layout 1 with the vertices' color values. The last parameter is multiplied by three as the previous 3 float values are from the vertices' positions
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Set the layout 2 with the vertices' texCoords values. The last parameter is multiplied by 6 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind the VBO and VAO so that unwanted changes cannot be done
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    //Bind the generate texture so that a texture image and a mipmap is assigned to it
    glBindTexture(GL_TEXTURE_2D, texture);

    //Set texture wrappings to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //When scaling a texture downwards, we linearly interpolate the two closest mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //When scaling a texture upwards, bilinear filtering will be used
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channelsInFile;
    const char* filePath = "./Assets/Textures/lava_texture.jpg";
    unsigned char* data = stbi_load(filePath, &width, &height, &channelsInFile, 0);

    if (data) {
        //The second zero or the sixth parameter should always be 0
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else {
        std::cout << "ERROR::TEXTURE::FILE_NOT_FOUND\n" << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);

    triangleShader.Use();
    triangleShader.SetInt("ourTexture", 0);

    //Engine loop
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double current = glfwGetTime();
        double delta = current - lastTime;
        processInput(window);
        update(delta);
        render(window, &triangleShader, texture, &VAO, &EBO);

        lastTime = current;
    }

    //Deallocation of all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    triangleShader.~Shader();
    glfwTerminate();

    return 0;
}

void init() {

}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void update(double delta) {
	
}

void render(GLFWwindow* window, Shader* shader, unsigned int texture, unsigned int* VAO, unsigned int* EBO) {
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Bind our EBO so that glDrawElements knows in what order we want the vertices to be drawn
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);

    shader->Use();
	glBindVertexArray(*VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}