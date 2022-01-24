#include "Game.h"

#include "SpriteRender.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Grid.h"
#include "Piece.h"
#include "TextRender.h"
#include "Client.h"
#include "Server.h"

SpriteRenderer *blockRender;
TextRenderer *text1;
Grid player1_grid = Grid(glm::vec2(0.0f, 0.0f));
Grid player2_grid = Grid(glm::vec2(1000, 0));
Piece player1 = Piece();
glm::vec2 pos = glm::vec2(0.0f, 0.0f);
glm::vec2 pos2 = glm::vec2(50.0f, 0.0f);
glm::vec2 size = glm::vec2(50.0f, 50.0f);
glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

bool Game::isOn = true;
std::string Game::name = "";
const float Game::WAIT_TIME = 0.14f;
const float Game::ROTATE_TIME = 0.14f;
const float Game::FALL_TIME = 0.25f;

void Game::Init() {
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
		static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
	ResourceManager::LoadShader("shaderBasic.vs", "fragBasic.fs", nullptr, "sprite");
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
	ResourceManager::LoadTexture("platformTile.png", false, "block");
	ResourceManager::LoadTexture("tetrisBG.png", false, "bg");

	blockRender = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	text1 = new TextRenderer(Game::SCR_WIDTH, Game::SCR_HEIGHT);
	text1->Load("zeldadxt.ttf", 24);
	player1_grid.Init(true);
	player2_grid.Init(false);
	player1.Spawn();
	return;
}

void Game::Update(float dt, GLFWwindow *window) {

	player1.culTime += dt;
	player1.fallTime += dt;
	player1.rotateTime += dt;

	player1.Update(Game::FALL_TIME, window, player1_grid);
	player1.Move(Game::WAIT_TIME, window, player1_grid);
	player1.Rotate(Game::ROTATE_TIME, window, player1_grid);

	std::string data = player1_grid.GetRawGrid();
	Client::SendData(data);

	if (Client::result.size() > 0) {
		std::string res_name = Server::DecodeName(Client::result);
		std::vector<int> data = Server::DecodeData(Client::result);
		if (res_name != Client::name && data.size() == 288) {
			player2_grid.OverrideGrid(data);
		}
	}
}

void Game::Render() {
	blockRender->DrawSprite(ResourceManager::GetTexture("bg"), glm::vec2(0.0f, 0.0f), glm::vec2(600.0f, 1200.0f), 0.0f, glm::vec3(1.0f));
	blockRender->DrawSprite(ResourceManager::GetTexture("bg"), glm::vec2(1000.0f, 0.0f), glm::vec2(600.0f, 1200.0f), 0.0f, glm::vec3(1.0f));
	//blockRender->DrawSprite(ResourceManager::GetTexture("block"), pos, size, 0.0f, color);
	player1.DrawOnGrid(player1_grid);
	player1_grid.Render(*blockRender);
	text1->RenderText(std::to_string(player1_grid.points) ,800, 100, 2);
	
	player2_grid.Render(*blockRender);
	text1->RenderText(std::to_string(player2_grid.points), 1800, 100, 2);

	return;
}


void Game::Destroy() {
	delete blockRender;
	delete text1;
	return;
}