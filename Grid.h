#ifndef GRID_H
#define GRID_H

#include "SpriteRender.h"
#include "Texture.h"
#include "main.h"

enum slotState {
	EMPTY = 0,
	RED = 1,
	BLUE = 2,
	GREEN = 3,
	YELLOW = 4,
	ORANGE = 5,
	PINK = 6,
	PURPLE = 7
};

class Grid {
public:
	static const int LENGTH = 12;
	static const int HEIGHT = 24;
	static const int SIZE = 50;
	glm::vec2 offset;
	//std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> renderGrid;
	Grid(glm::vec2 offset);
	Grid();
	void Init(bool isControl);
	void changeSlot(int x, int y, slotState newState);
	void Render(SpriteRenderer &sprite);
	int CheckSlot(int x, int y);
	int points;
	void getPoints();
	void endGame(GLFWwindow *window, bool alive);
	std::string GetRawGrid();
	void OverrideGrid(std::vector<int> rawData);
	bool isMut;
private:
	std::vector<int> getFullRows();
};

#endif