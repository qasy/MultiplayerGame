#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(const std::string& serverAddress, int serverPort)
    : serverAddress(serverAddress), serverPort(serverPort), sock(-1) {}

ConnectionManager::~ConnectionManager() {
    stop();
}

void ConnectionManager::start() {
    running = true;
    thread = std::thread(&ConnectionManager::run, this);
}

void ConnectionManager::stop() {
    running = false;
    cv.notify_all(); // Уведомляем поток о завершении
    if (thread.joinable()) {
        thread.join();
    }
    if (sock != -1) {
        close(sock);
    }
}

void ConnectionManager::updateCoordinates(int x, int y)
{
    if (playerX != x || playerY != y) // Проверяем, изменились ли координаты
    {
        std::lock_guard<std::mutex> lock(coordsMutex); // Защита доступа к координатам
        playerX = x;
        playerY = y;
        coordsChanged = true; // Указываем, что координаты изменились
        cv.notify_one(); // Уведомляем поток
    }
}

void ConnectionManager::run() {
    // Создаем сокет
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return;
    }

    // Настраиваем адрес сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

    // Подключаемся к серверу
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection to server failed\n";
        close(sock);
        sock = -1;
        return;
    }

    // Отправляем координаты в основном цикле
    while (running) {
        std::unique_lock<std::mutex> lock(coordsMutex);
        cv.wait(lock, [this] { return coordsChanged || !running; }); // Ждем уведомления

        if (!running) break; // Если остановлено, выходим из цикла

        std::string message = std::to_string(playerX) + "," + std::to_string(playerY);
        send(sock, message.c_str(), message.size(), 0); // Отправляем координаты

        coordsChanged = false; // Сбрасываем флаг изменений
    }
}
