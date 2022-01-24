#include "Client.h"
#include <mutex>

std::mutex m;
#define PORT 1234

ENetHost * Client::client;
ENetAddress Client::address;
ENetEvent Client::event;
ENetPeer * Client::peer;
ENetPacket * Client::packet;
std::string Client::name;
std::string Client::result;

void Client::Init(std::string name) {
	Client::name = name;

	std::string temp;
	if (enet_initialize() != 0) {
		std::cout << "Enet could not load properly";
		std::cin >> temp;
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);

	client = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);
	if (client == nullptr) {
		std::cout << "Failed to create Client";
		std::cin >> temp;
		exit(EXIT_FAILURE);
	}

	enet_address_set_host(&address, "localhost");
	address.port = 7777;

	peer = enet_host_connect(client, &address, 2, 0);
	if (peer == NULL) {
		std::cout << "Could not connect to Server" << std::endl;
		std::cin >> temp;
		exit(EXIT_FAILURE);
	}

	if (enet_host_service(client, &event, 2000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
		std::cout << "Connected to Server" << std::endl;
		//packet = enet_packet_create(name.c_str(), strlen(name.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
		//enet_peer_send(peer, 0, packet);
	}
	else {
		enet_peer_reset(peer);
		std::cout << "Could not connect to " << PORT << std::endl;
		std::cin >> temp;
		exit(EXIT_FAILURE);
	}

}

std::string Client::Update() {
	if (enet_host_service(client, &event, 1000) > 0) {
		switch (event.type) {
		case ENET_EVENT_TYPE_RECEIVE:
			std::cout << event.packet->data << std::endl;
			return (char*)event.packet->data;
			break;
		}
	}
	return "";
}

void run(std::atomic<bool> & running) {
	while (running) {
		while (enet_host_service(Client::client, &Client::event, 100) > 0) {
			switch (Client::event.type) {
			case  ENET_EVENT_TYPE_RECEIVE:
				//std::cout << Client::event.packet->data << std::endl;
				m.lock();
				Client::result = std::string((char*)Client::event.packet->data);
				//std::cout << Client::result.length() << std::endl;
				m.unlock();
				enet_packet_destroy(Client::event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("(Client) %s disconnected.\n", Client::event.peer->data);
				// Reset client's information
				Client::event.peer->data = NULL;
				break;
			}
		}
	}
	enet_peer_disconnect(Client::peer, 0);
	Client::CleanUp();
}


void Client::SendData(std::string data) {
	std::string msg = Client::name + ":" + data;
	packet = enet_packet_create(msg.c_str(), strlen(msg.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

void Client::CleanUp() {
	enet_deinitialize();
}