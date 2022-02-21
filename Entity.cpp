#include "Entity.h"
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;

Entity::Entity()
    : front_y(-1), front_x(-1), val_y1(-1), val_x1(-1), val_y2(-1), val_x2(-1)
{
    isplaced = 0;
    id = -1;
    size = 0;
    membership = '-';
    body = nullptr;
    strcpy(type, "?");
    direction = '?';
}

Reef::Reef(int y, int x)
    :Entity()
{
    front_y = y;
    front_x = x;
    body = new char;
    *body = '#';
}

void Entity::set_val(int y1, int x1, int y2, int x2)
{
    val_x1 = x1;
    val_x2 = x2;
    val_y1 = y1;
    val_y2 = y2;
}

Entity::~Entity()
{
    delete[] body;
}