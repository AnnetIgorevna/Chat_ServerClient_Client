//#include <iostream>
//#include <unistd.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>

#include "Chat_ClientTCP.h"

//using namespace std;
//
//#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
//#define PORT 7777 // Будем использовать этот номер порта
//
//int socket_file_descriptor, connection;
//struct sockaddr_in serveraddress, client;
//char message[MESSAGE_LENGTH];
int main() {

    Chat_ClientTCP client;

    if (client.createSock())
    {
        client.connectServer();
    }

    return 0;
}
