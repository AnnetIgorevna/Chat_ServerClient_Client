#pragma once

#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include <arpa/inet.h>

#define MESSAGE_LENGTH 1024 // Ìàêñèìàëüíûé ðàçìåð áóôåðà äëÿ äàííûõ
#define PORT 7777 // Áóäåì èñïîëüçîâàòü ýòîò íîìåð ïîðòà

class Chat_ClientTCP
{
public:
	~Chat_ClientTCP();
	bool createSock();
	void connectServer();
	void communication();
private:
	struct sockaddr_in serveraddress, client;
	int socket_file_descriptor, connection;
	char message[MESSAGE_LENGTH];
};
