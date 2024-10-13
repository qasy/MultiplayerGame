#ifndef PLAYER_H
#define PLAYER_H

class Player 
{
public:
    Player(int x = 0, int y = 0);

    int getId() const;
    int getX() const;
    int getY() const;

    // void setPosition(int x, int y);
    void move();

private:
    static int global_id_counter;
    int id;
    int x;
    int y;

};

#endif // PLAYER_H
