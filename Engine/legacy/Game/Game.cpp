#include "Game.h"

#include "../ECS/Entity/Entity.h"
#include "../ECS/Component/Types/MeshComponent.h"
#include "../Managers/InputManager/InputManager.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

using glm::mat4;
using glm::vec3;

Game::Game(int p_width, int p_height) : m_currentState(Start), currentTime(0.0), delta(0.0), counter(0), lightPos(0.0f, 2.0f, 3.0f) {
	//m_renderer = std::make_unique<Renderer>(p_width, p_height, 45.0f);
	//
	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	//	std::cout << "Failed to initialize GLAD" << std::endl;
	//}

	//m_guiManager = std::make_unique<Cannis::GuiManager>(m_renderer->getWindow(), p_width, p_height);
	//m_renderer->init();

	//m_shaderManager = std::make_unique<Cannis::ShaderManager>();
	//m_shaderManager->useShader(ShaderSlot::Blinn_Phong);

	//InputManager::start(m_renderer->mainCamera);

	//lastTime = glfwGetTime();
}

Game::~Game() {
	//m_renderer->clean();
	//m_shaderManager->clean();
}

void Game::initialize() {
	m_guiManager->init();



	shared_ptr<Entity> entity1 = Registry::getInstance().createEntity();
	//entity1->addComponent<MeshComponent>();
}

void Game::run() {
	setup();
	start();
	while (m_currentState == GameState::Update) {
		currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		counter++;
		if (delta > 1.0f / 30.0f) {
			double fps = (1.0 / delta) * counter;
			double ms = (delta / counter) * 1000;

			lastTime = currentTime;
			counter = 0;
		}
		processInput();
		update();
		render();
	}
	destroy();
}

void Game::setup() {
	
}

void Game::start() {
	m_currentState = GameState::Update;

	currentModel = Model("f22.obj", false);
	currentModel.addTexture("f22.png", false);
}

void Game::update() {
	//mat4 model = mat4(1.0f);
	//model = glm::scale(model, vec3(2.0f, 2.0f, 2.0f));
	//float angle = static_cast<float>(delta);
	//model = glm::rotate(model, glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));
	//m_shaderManager->setMatrix4(m_renderer->currentShader, "model", model);

	////the camera coordinates
	//mat4 view = mat4(1.0f);
	//view = m_renderer->mainCamera->getViewMatrix();
	//m_shaderManager->setMatrix4(m_renderer->currentShader, "view", view);

	////We assign the world camera to use projection perspective
	//mat4 projection = mat4(1.0f);
	//projection = glm::perspective(glm::radians(m_renderer->fieldOfView), float(m_renderer->screenWidth / m_renderer->screenHeight), 0.1f, 100.0f);
	//m_shaderManager->setMatrix4(m_renderer->currentShader, "projection", projection);

	//m_shaderManager->setVec3(m_renderer->currentShader, "viewPos", m_renderer->mainCamera->position);

	//m_shaderManager->setVec3(m_renderer->currentShader, "lightPos", lightPos);
	//m_shaderManager->setInt(m_renderer->currentShader, "blinn", 1);
}

void Game::render() {
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	////We clear the zbuffer as the model will change coordinates each cycle
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_guiManager->update();

	//m_shaderManager->useShader(m_renderer->currentShader);
	//currentModel.draw(m_shaderManager->getShader(m_renderer->currentShader));

	//m_guiManager->lateUpdate();

	//glfwSwapBuffers(m_renderer->getWindow());
}

void Game::destroy() {
	//glfwSetWindowShouldClose(m_renderer->getWindow(), true);
}

void Game::processInput() {
	//glfwPollEvents();

	//if (glfwGetKey(m_renderer->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	//	m_currentState = GameState::Destroy;
	//}

	//if (glfwGetKey(m_renderer->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
	//	std::cout << "Forward" << std::endl;
	//	m_renderer->mainCamera->moveCamera(FORWARD, delta);
	//}

	//if (glfwGetKey(m_renderer->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	//	m_renderer->mainCamera->moveCamera(BACKWARD, delta);

	//if (glfwGetKey(m_renderer->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	//	m_renderer->mainCamera->moveCamera(RIGHT, delta);

	//if (glfwGetKey(m_renderer->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	//	m_renderer->mainCamera->moveCamera(LEFT, delta);
}

void Game::changeState(GameState p_newState) {

}