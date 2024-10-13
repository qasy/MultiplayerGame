#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <iostream>
#include <thread>
#include <atomic>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <mutex>
#include <condition_variable>

class ConnectionManager {
public:
    ConnectionManager(const std::string& serverAddress, int serverPort);
    ~ConnectionManager();

    void start();
    void stop();
    void updateCoordinates(int x, int y);

private:
    void run();

    std::string serverAddress;
    int serverPort;
    int sock;
    std::thread thread;
    std::atomic<bool> running{false};
    
    std::mutex coordsMutex;
    std::condition_variable cv; // Условная переменная
    int playerX{0}, playerY{0}; // Координаты игрока
    bool coordsChanged{false}; // Флаг изменения координат
};

#endif // CONNECTION_MANAGER_H
