#include <ncurses.h> // Для работы с ncurses
#include "Player.h"

int Player::global_id_counter = 0;

Player::Player(int x, int y) : x(x), y(y) 
{
    id = Player::global_id_counter++;
}

int Player::getId() const { return id; }

int Player::getX() const { return x; }
int Player::getY() const { return y; }

// void Player::setPosition(int x, int y) 
// {
//     this->x = x;
//     this->y = y;
// }

void Player::move()
{
    int input = getch(); // Получаем нажатие клавиши
    switch (input) 
    {
        case KEY_UP: // Вверх
            --y;
            break;
        case KEY_DOWN: // Вниз
            ++y;
            break;
        case KEY_LEFT: // Влево
            --x;
            break;
        case KEY_RIGHT: // Вправо
            ++x;
            break;
    }
}
