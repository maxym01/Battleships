#pragma once
#include "Entity.h"
#include "Player.h"

class Entity;

class Player;

class Reef;

class Board
{
private:
    int height, width;
    char** tab; //tablica s³u¿¹ca do wyœwietlania planszy
    Entity*** tabr; //które pola tablicy s¹ zajête przez statek/rafê
public:
    Board(int height, int width);
    const void print();
    void place_ship(Entity* ship, int sum, bool state, Player* p);
    void check_placement(Entity* ship, int y, int x, char* C, bool state, int number);
    void place_reef(Reef* reef);
    const void count(Player* A, Player* B);
    void shoot(Player* p, Player* A, Player* B);
    int make_state(Entity* ship);
    void create_table(int height, int width);
    void move(Entity* ship, int sum, Player* p);
    void forward(Entity* ship);
    void right(Entity* ship, int y, int x);
    void left(Entity* ship, int y, int x);
    friend class Player;
    ~Board();
};