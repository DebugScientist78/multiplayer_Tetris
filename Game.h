#ifndef GAME_H
#define GAME_H

#include "main.h"

class Game {
public:
	// settings
	static const unsigned int SCR_WIDTH = 2000;
	static const unsigned int SCR_HEIGHT = 1200;
	static std::string name;
	static const float WAIT_TIME;
	static const float FALL_TIME;
	static const float ROTATE_TIME;
	static bool isOn;

	static void Init();
	static void Update(float dt, GLFWwindow *window);
	static void Render();
	static void Destroy();
private:
	Game() { }
};

#endif