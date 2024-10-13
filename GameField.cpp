// #include <ncurses.h> // Для работы с ncurses
#include "GameField.h"
#include "Player.h"

GameField::GameField(int width, int height) : WIDTH{width}, HEIGHT{height}, field(height, std::vector<char>(width, '.')) 
{
    initscr();            // Инициализируем ncurses
    keypad(stdscr, TRUE); // Включаем поддержку клавиш-стрелок
    noecho();             // Отключаем вывод нажатых клавиш
    curs_set(0);          // Скрываем курсор
}

GameField::~GameField()
{
    endwin(); // Завершаем работу ncurses
}

void GameField::drawField(const Player& player)
{
    // Заполняем вектор дефолтными значениями
    for (auto& row : field) 
    {
        for (auto& symbol : row) 
        {
            symbol = '.';
        }
    }

    // Вытаскиваем координаты игроков
    int x = player.getX();
    int y = player.getY();
    if((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
    {
        field[y][x] = static_cast<char>(player.getId() + 43); // 48 - shift to numbers in ASCII
    }

    clear(); // Очищаем окно
    // Отрисовываем
    for (const auto& row : field) 
    {
        for (const auto& symbol : row) 
        {
            char ch[1];
            ch[0] = symbol;
            printw(ch);
            printw(" ");
        }
        printw("\n");
    }
    refresh(); // Обновляем экран
}

void GameField::drawField(const std::vector<Player>& players) 
{
    // Заполняем вектор дефолтными значениями
    for (auto& row : field) 
    {
        for (auto& symbol : row) 
        {
            symbol = '.';
        }
    }

    // Извлекаем координаты игроков
    for(const auto& player : players)
    {
        int x = player.getX();
        int y = player.getY();
        if((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
        {
            field[y][x] = static_cast<char>(player.getId() + 48); // 48 - shift to numbers in ASCII
        }
    }

    clear(); // Очищаем экран
    for(std::size_t x = 0; x < getWidth(); ++x)
    {
        for(std::size_t y = 0; x < getHeight(); ++y)
        {
            printw(static_cast<const char*>(".")); // Остальная часть поля
        }
        printw("\n");
    }
    refresh(); // Обновляем экран
}

int GameField::getWidth() const
{
    return WIDTH;
}

int GameField::getHeight() const
{
    return HEIGHT;
}