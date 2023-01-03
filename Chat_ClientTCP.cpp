#include "Chat_ClientTCP.h"

Chat_ClientTCP::~Chat_ClientTCP()
{
	// ��������� �����, ��������� ����������
	close(socket_file_descriptor);
}

bool Chat_ClientTCP::createSock()
{
    // �������� �����
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Creation of Socket failed!" << std::endl;
        return false;
    }

    // ��������� ����� 
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // ������� ����� �����
    serveraddress.sin_port = htons(PORT);
    // ���������� IPv4
    serveraddress.sin_family = AF_INET;
	return true;
}

void Chat_ClientTCP::connectServer()
{
    // ��������� ���������� � ��������
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        std::cout << "Connection with the server failed!" << std::endl;
        exit(1);
    }
    std::cout << "Connection with the server is Ok..." << std::endl;
    communication();
}

void Chat_ClientTCP::communication()
{
    // �������������� � ��������
    while (1) {
        // ������ ��������� �� �������
        bzero(message, sizeof(message));
        // ���� ������ �� �������
        read(socket_file_descriptor, message, sizeof(message));
        std::cout << "Message from server: " << message << std::endl;
        
        // �������� ��������� �������
        bzero(message, sizeof(message));
        std::cout << "Message from client: ";
        std::cin.getline(message, MESSAGE_LENGTH);
        if ((strncmp(message, "end", 3)) == 0) {
            write(socket_file_descriptor, message, sizeof(message));
            std::cout << "Client Exit" << std::endl;
            std::cout << "Press any key to exit..." << std::endl;
            std::cin.get();
            return;
        }
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        // ���� �������� >= 0  ����, ������ ��������� ������ �������
        if (bytes >= 0) {
            std::cout << "Data send to the server successfully!" << std::endl;
        }

    }
}
