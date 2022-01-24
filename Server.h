#ifndef SERVER_H
#define SERVER_H

#include <enet/enet.h>
#include "Grid.h"
#include "Piece.h"

class Server {
public:

	static std::vector<std::vector<int>> player1_grid;
	static std::vector<std::vector<int>> player2_grid;

	static void Init();
	static void Run();
	static void CleanUp();

	static std::vector<int> DecodeData(std::string data);
	static std::string DecodeName(std::string data);

private:
	Server() {};
};

#endif