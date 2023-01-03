#include "Chat_ClientTCP.h"

Chat_ClientTCP::~Chat_ClientTCP()
{
	// закрываем сокет, завершаем соединение
	close(socket_file_descriptor);
}

bool Chat_ClientTCP::createSock()
{
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Creation of Socket failed!" << std::endl;
        return false;
    }

    // Установим адрес 
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
	return true;
}

void Chat_ClientTCP::connectServer()
{
    // Установим соединение с сервером
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
    // Взаимодействие с сервером
    while (1) {
        // чтение сообщения от сервера
        bzero(message, sizeof(message));
        // Ждем ответа от сервера
        read(socket_file_descriptor, message, sizeof(message));
        std::cout << "Message from server: " << message << std::endl;
        
        // отправка сообщения серверу
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
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if (bytes >= 0) {
            std::cout << "Data send to the server successfully!" << std::endl;
        }

    }
}
