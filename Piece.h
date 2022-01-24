#ifndef PIECE_H
#define PIECE_H

#include "Grid.h"
#include "main.h"

class Piece {
public:
	bool isAlive;

	Piece();
	void Spawn();
	void DrawOnGrid(Grid &assignedGrid);
	void Move(float waitTime, GLFWwindow *window, Grid &assignedGrid);
	void Rotate(float rotTime, GLFWwindow *window, Grid &assignedGrid);
	void Update(float waitTime, GLFWwindow *window, Grid &assignedGrid);
	void Kill();
	float culTime;
	float rotateTime;
	float fallTime;
private:
	slotState colorState;
	glm::vec2 displacement;
	glm::vec2 pivot;
	std::vector<glm::vec2> disps;
	std::vector<glm::vec2> positions;
	bool CheckCollision(int key, Grid &assignedGrid);
};

#endif