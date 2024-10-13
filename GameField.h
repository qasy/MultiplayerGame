#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include <iostream>
#include <ncurses.h> // Для работы с ncurses
#include "Player.h"

class GameField 
{
public:
    GameField(int width = 10, int height = 10);
    ~GameField();
    void drawField(const std::vector<Player>& players);
    void drawField(const Player& player);

    int getWidth() const;
    int getHeight() const;

private:
    WINDOW* gameWindow; // Окно для игрового поля

    const int WIDTH;
    const int HEIGHT;

    std::vector<std::vector<char>> field;

};

#endif // GAMEFIELD_H
