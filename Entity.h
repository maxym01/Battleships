#pragma once
#include "Player.h"
#include "Board.h"

class Entity
{
protected:
    int front_y, front_x, id, size, val_y1, val_x1, val_y2, val_x2;
    char membership;
    char* body;
    char type[3];
    char direction;
    bool isplaced;
public:
    Entity();
    void set_val(int y1, int x1, int y2, int x2);
    friend class Board;
    friend class Player;
    ~Entity();
};

class Reef : public Entity
{
public:
    Reef(int y, int x);
};