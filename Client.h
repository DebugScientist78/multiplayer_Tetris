#ifndef CLIENT_H
#define CLIENT_H

#include <enet/enet.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>

void run(std::atomic<bool> & running);

class Client {
public:
	static ENetHost * client;
	static ENetAddress address;
	static ENetEvent event;
	static ENetPeer * peer;
	static ENetPacket * packet;
	static std::string name;
	static std::string result;
	static void Init(std::string name);
	static std::string Update();
	//static void Run(std::atomic<bool> running);
	static void SendData(std::string data);
	static void CleanUp();
private:
	Client() {};
};

#endif