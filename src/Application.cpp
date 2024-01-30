#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(int width, int height);
void processInput(GLFWwindow* window);
void update(float delta);
void render(GLFWwindow* window);

int main()
{
	const int initialScreenWidth = 800;
	const int initialScreenHeight = 600;

	//Initialize GLFW for the 4.5 OpenGL version using the Core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(initialScreenWidth, initialScreenHeight, "Cannis Canno Engine", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	//Now that GLAD has finished we can start using OpenGL functions
	framebufferSizeCallback(initialScreenWidth, initialScreenWidth);

	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double current = glfwGetTime();
		double delta = current - lastTime;

		processInput(window);
		update(delta);
		render(window);

		lastTime = current;
	}


	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void update(float delta) {

}

void render(GLFWwindow* window) {
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}