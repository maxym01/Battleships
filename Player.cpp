#include "Player.h"
#include "Entity.h"
#include<iostream>
#pragma warning(disable : 4996)
using namespace std;

Player::Player(char id)
    : id(id)
{
    sum_ships = 0;
    score = 0;
    ship = nullptr;
}

void Player::set_fleet(int car, int bat, int cru, int des)
{
    int j;
    sum_ships = car + bat + cru + des;
    ship = new Entity[sum_ships];
    for (int i = 0; i < sum_ships; i++)
    {
        ship[i].membership = id;
        if (id == 'A')
        {
            ship[i].val_y1 = 0;
            ship[i].val_x1 = 0;
            ship[i].val_y2 = 9;
            ship[i].val_x2 = 9;

        }
        else if (id == 'B')
        {
            ship[i].val_y1 = 11;
            ship[i].val_x1 = 0;
            ship[i].val_y2 = 20;
            ship[i].val_x2 = 9;
        }
        if (i < car)
        {
            ship[i].id = i;
            strcpy(ship[i].type, "CAR");
            j = 5;
        }
        else if (i >= car && i < car + bat)
        {
            ship[i].id = i - car;
            strcpy(ship[i].type, "BAT");
            j = 4;
        }
        else if (i >= car + bat && i < car + bat + cru)
        {
            ship[i].id = i - (car + bat);
            strcpy(ship[i].type, "CRU");
            j = 3;
        }
        else
        {
            ship[i].id = i - (car + bat + cru);
            strcpy(ship[i].type, "DES");
            j = 2;
        }
        ship[i].body = new char[j];
        for (int k = 0; k < j; k++)
        {
            ship[i].body[k] = '+';
            score++;
        }
        ship[i].size = j;
    }
}

int Player::get_sum()
{
    return sum_ships;
}

Entity* Player::get_ship()
{
    return ship;
}