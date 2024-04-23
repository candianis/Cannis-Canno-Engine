#pragma once

class Game {
public:

private:
	GameState m_currentState;

};

enum GameState {
	Start,
	Update,
	LateUpdate,
	Standby,
	Finish,
	CleanUp
};