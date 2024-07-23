#pragma once

#include "../ECS/Registry/Registry.h"
#include "../Managers/ShaderManager/ShaderManager.h"
#include "../Managers/GuiManager/GuiManager.h"
#include "../Managers/AssetManager/AssetManager.h"
#include "../Renderer/Renderer.h"
#include "../Model/Model.h"
#include "../Light/Light.h"

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using std::unique_ptr;
using std::shared_ptr;
using glm::vec3;
using std::string;

enum GameState;

class Game {
public:
	double lastTime;
	double currentTime;
	double delta;
	size_t counter;

	Model currentModel;
	glm::vec3 lightPos;

	Game(int p_width, int p_height);
	~Game();

	// @brief Initialize all thw window and UI systems
	void initialize();

	// @brief Wrapper for the game loop
	void run();

	// @brief Prepares all the Systems that will be present in the 
	void setup();

	// @brief 
	void start();

	void processInput();

	void update();

	void render();

	void destroy();

private:
	GameState m_currentState;

	unique_ptr<Renderer> m_renderer;
	unique_ptr<Cannis::ShaderManager> m_shaderManager;
	unique_ptr<Cannis::GuiManager> m_guiManager;
	unique_ptr<Cannis::AssetManager> m_assetManager;

	void changeState(GameState p_newState);
};

enum GameState {
	Start,
	Update,
	Standby,
	Destroy
};