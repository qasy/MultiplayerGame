#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "ConnectionManager.h"
#include "GameField.h"


// Основной игровой цикл
int main() 
{
    std::string server_ip = "127.0.0.1";
    // std::string server_ip = "154.59.110.90";
    
    GameField field(10, 10);
    Player player(0, 0);
    // ConnectionManager connectionManager(server_ip, 8080); // Замените на адрес вашего сервера
    // connectionManager.start(); // Запускаем поток соединения с сервером

    while (true) 
    {
        field.drawField(player);
        player.move(); // Обрабатываем перемещение игрока
        // connectionManager.updateCoordinates(player.getX(), player.getY()); // Отправляем координаты
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(50ms);
    }
    return 0;
}
