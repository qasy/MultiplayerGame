#include <iostream>
#include <thread>
#include <vector>
#include <functional> // Для std::bind
#include <mutex>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include "Player.h" // Заголовок для класса Player

class GameServer {
public:
    GameServer(int port);
    void startServer();

private:
    void handleClient(int clientSocket, Player& player);
    std::vector<Player> players;
    std::mutex playersMutex;
    int serverSocket;
};

GameServer::GameServer(int port) {
    // Создаем сокет
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Настраиваем адрес сервера
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Привязываем сокет
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Начинаем слушать соединения
    listen(serverSocket, 5);
    std::cout << "Server started on port " << port << std::endl;
}

void GameServer::startServer() {
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }

        static int id = 0;
        // Создаем нового игрока
        Player newPlayer(id++, 0, 0);

        // Добавляем игрока в вектор
        {
            std::lock_guard<std::mutex> lock(playersMutex);
            players.push_back(newPlayer);
        }

        // Запускаем поток для обработки клиента
        std::thread clientThread(std::bind(&GameServer::handleClient, this, clientSocket, std::ref(newPlayer)));
        clientThread.detach(); // Отделяем поток
    }
}

void GameServer::handleClient(int clientSocket, Player& player) {
    // Логика обработки клиента
    std::cout << "Handling client..." << std::endl;
    
    // Например, отправляем сообщение игроку
    const char* welcomeMessage = "Welcome to the game!\n";
    send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);

    // Закрываем сокет после завершения работы с клиентом
    close(clientSocket);
}

int main() {
    GameServer server(8080); // Запуск сервера на порту 8080
    server.startServer();
    return 0;
}
