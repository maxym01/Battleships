#pragma once
#include "Entity.h"

class Entity;

class Player
{
private:
    char id;
    int sum_ships;
    int score;
    Entity* ship;
public:
    Player(char id);
    void set_fleet(int car, int bat, int cru, int des);
    int get_sum();
    friend class Board;
    friend int main();
    Entity* get_ship();
};