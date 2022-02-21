#include "Board.h"
#include "Entity.h"
#include <iostream>
#pragma warning(disable : 4996)
//visual studio 2019 nie pozwala ma uzycie strcpy
using namespace std;


Board::Board(int height, int width)
{
    this->height = height;
    this->width = width;
    tab = new char* [height];
    tabr = new Entity * *[height];
    for (int i = 0; i < height; i++)
    {
        tab[i] = new char[width];
        tabr[i] = new Entity * [width];
        for (int j = 0; j < width; j++)
        {
            tab[i][j] = ' ';
            tabr[i][j] = nullptr;
        }
    }
}

const void Board::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << tab[i][j];
        }

        cout << '\n';
    }
}

void Board::place_ship(Entity* ship, int sum, bool state, Player* p)
{
    int y, x, id, number=0;
    char d[4]; 
    char* D = d;
    char C[4];
    static int id_dup = -1;
    static char C_dup[3] = { ' ',' ' ,' ' };
    static char owner;
    cin >> y >> x >> C >> id;
    strcpy(D, C);
    cin >> C;
    try {
        if (id_dup == id && !strcmp(C_dup, C) && owner==p->id)
            throw id;
    }
    catch (int err) {
        cout << "INVALID OPERATION " << '"' << "PLACE_SHIP " << y << " " << x << " " << d << " " << err << " " << C << '"' << ": SHIP ALREADY PRESENT";
        exit(0);
    }
    id_dup = id;
    strcpy(C_dup, C);
    owner = p->id;
    for (int i = 0; i < sum; i++)
    {
        if (!strcmp(ship[i].type, C) && ship[i].id == id)
        {
            if (state)
                number = Board::make_state(&ship[i]);
            try {
                if (y > ship[i].val_y2 || y<ship[i].val_y1 || x>ship[i].val_x2 || x < ship[i].val_x1)
                    throw y;
                ship[i].front_y = y;
                ship[i].front_x = x;
                ship[i].isplaced = 1;
                tabr[y][x] = &ship[i];
                tab[y][x] = ship[i].body[0];
                if (!strcmp(d, "N"))
                {
                    tabr[y][x]->direction = 'N';
                    Board::check_placement(&ship[i], y, x, C, state, number);
                    for (int a = 1; a < (ship[i].size); a++)
                    {
                        if (y + a > ship[i].val_y2 || y + a<ship[i].val_y1 || x>ship[i].val_x2 || x < ship[i].val_x1)
                            throw y;
                        Board::check_placement(&ship[i], y + a, x, C, state, number);
                        tab[y + a][x] = ship[i].body[a];
                        tabr[y + a][x] = &ship[i];
                    }
                }
                else if (!strcmp(d, "E"))
                {
                    tabr[y][x]->direction = 'E';
                    Board::check_placement(&ship[i], y, x, C, state, number);
                    for (int a = 1; a < ship[i].size; a++)
                    {
                        if (y > ship[i].val_y2 || y<ship[i].val_y1 || x - a>ship[i].val_x2 || x - a < ship[i].val_x1)
                            throw y;
                        Board::check_placement(&ship[i], y, x - a, C, state, number);
                        tab[y][x - a] = ship[i].body[a];
                        tabr[y][x - a] = &ship[i];
                    }
                }
                else if (!strcmp(d, "S"))
                {
                    tabr[y][x]->direction = 'S';
                    Board::check_placement(&ship[i], y, x, C, state, number);
                    for (int a = 1; a < ship[i].size; a++)
                    {
                        if (y - a > ship[i].val_y2 || y - a<ship[i].val_y1 || x>ship[i].val_x2 || x < ship[i].val_x1)
                            throw y;
                        Board::check_placement(&ship[i], y - a, x, C, state, number);
                        tab[y - a][x] = ship[i].body[a];
                        tabr[y - a][x] = &ship[i];
                    }
                }
                else if (!strcmp(d, "W"))
                {
                    tabr[y][x]->direction = 'W';
                    Board::check_placement(&ship[i], y, x, C, state, number);
                    for (int a = 1; a < ship[i].size; a++)
                    {
                        if (y > ship[i].val_y2 || y<ship[i].val_y1 || x + a>ship[i].val_x2 || x + a < ship[i].val_x1)
                            throw y;
                        Board::check_placement(&ship[i], y, x + a, C, state, number);
                        tab[y][x + a] = ship[i].body[a];
                        tabr[y][x + a] = &ship[i];
                    }
                }
            }
            catch (int err) {
                cout << "INVALID OPERATION " << '"' << "PLACE_SHIP " << err << " " << x << " " << d << " " << id << " " << C << '"' << ": NOT IN STARTING POSITION";
                exit(0);
            }
            return;
        }
        else
            continue;
    }
    cout << "INVALID OPERATION " << '"' << "PLACE_SHIP " << y << " " << x << " " << d << " " << id << " " << C << '"' << ": ALL SHIPS OF THE CLASS ALREADY SET";
    exit(0);
}

void Board::check_placement(Entity* ship, int y, int x, char* C, bool state, int number)
{
    if (tab[y][x] == '#')
    {
        if (state == 0)
            cout << "INVALID OPERATION " << '"' << "PLACE_SHIP " << ship->front_y << " " << ship->front_x << " " << ship->direction << " " << ship->id << " " << C << '"' << ": PLACING SHIP ON REEF";
        else
            cout << "INVALID OPERATION " << '"' << "SHIP " << ship->membership << " " << ship->front_y << " " << ship->front_x << " " << ship->direction << " " << ship->id << " " << C << " " << number << '"' << ": PLACING SHIP ON REEF";
        exit(0);
    }
    for (int a = y - 1; a < y + 2; a++)
    {
        for (int b = x - 1; b < x + 2; b++)
        {
            if (a >= 0 && b >= 0 && a < height && b < width && tab[a][b] != ' ' && tab[a][b] != '#')
            {
                if (tabr[a][b] != nullptr && (tabr[a][b]->membership != ship->membership || tabr[a][b]->id != ship->id || strcmp(tabr[a][b]->type, ship->type)))
                {
                    if (state == 0)
                        cout << "INVALID OPERATION " << '"' << "PLACE_SHIP " << ship->front_y << " " << ship->front_x << " " << ship->direction << " " << ship->id << " " << C << '"' << ": PLACING SHIP TOO CLOSE TO OTHER SHIP";
                    else
                        cout << "INVALID OPERATION " << '"' << "SHIP " << ship->membership << " " << ship->front_y << " " << ship->front_x << " " << ship->direction << " " << ship->id << " " << C << " " << number << '"' << ": PLACING SHIP TOO CLOSE TO OTHER SHIP";
                    exit(0);
                }
            }
        }
    }
}

void Board::place_reef(Reef* reef)
{
    tabr[reef->front_y][reef->front_x] = reef;
    tab[reef->front_y][reef->front_x] = *reef->body;
}

const void Board::count(Player* A, Player* B)
{
    int a = 0, b = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tabr[i][j]!=nullptr && tab[i][j] == '+' && tabr[i][j]->membership == 'A')
                a++;
            if (tabr[i][j] != nullptr && tab[i][j] == '+' && tabr[i][j]->membership == 'B')
                b++;
        }
    }
    cout << "PARTS REMAINING:: A : " << a << " B : " << b << endl;
    A->score = a;
    B->score = b;
}

void Board::shoot(Player* p, Player* A, Player* B)
{
    int y, x;
    try {
        cin >> y >> x;
        if (y > 21)
            throw y;
        if (x > 10)
            throw x;
    }
    catch (int err) {
        cout << "INVALID OPERATION " << '"' << "SHOOT " << y << " " << x << '"' << ": FIELD DOES NOT EXIST";
        exit(0);
    }
    bool check = 0;
    for (int i = 0; i < A->sum_ships; i++)
    {
        if (A->ship[i].isplaced == 0)
            check = 1;
    }
    for (int i = 0; i < B->sum_ships; i++)
    {
        if (B->ship[i].isplaced == 0)
            check = 1;
    }
    if (check)
    {
        cout << "INVALID OPERATION " << '"' << "SHOOT " << y << " " << x << '"' << ": NOT ALL SHIPS PLACED";
        exit(0);
    }
    if (tabr[y][x] != nullptr)
    {
        tabr[y][x]->body[(tabr[y][x]->front_y) - y] = 'x';
        tab[y][x] = tabr[y][x]->body[(tabr[y][x]->front_y) - y];
        if (tabr[y][x]->membership == 'A')
            A->score--;
        else if (tabr[y][x]->membership == 'B')
            B->score--;
    }
    if (A->score == 0)
    {
        cout << "B won";
        exit(0);
    }
    else if (B->score == 0)
    {
        cout << "A won";
        exit(0);
    }
}

void Board::create_table(int height, int width) 
{
    Board::~Board();
    this->height = height;
    this->width = width;
    tab = new char* [height];
    tabr = new Entity * *[height];
    for (int i = 0; i < height; i++)
    {
        tab[i] = new char[width];
        tabr[i] = new Entity * [width];
        for (int j = 0; j < width; j++)
        {
            tab[i][j] = ' ';
            tabr[i][j] = nullptr;
        }
    }
}

int Board::make_state(Entity* ship)
{
    int sequence, i = (ship->size) - 1, number;
    bool* state = new bool[ship->size];
    cin >> sequence;
    number = sequence;
    while (sequence > 0)
    {
        int digit = sequence % 10;
        sequence /= 10;
        state[i] = digit;
        i--;
    }
    for (int i = 0; i < ship->size; i++)
    {
        if (state[i] == 0)
            ship->body[i] = 'x';
        else continue;
    }
    delete[] state;
    return number;
}

void Board::move(Entity* ship, int sum, Player* p)
{
    int j;
    char C[4], D[4];
    cin >> j >> C;
    strcpy(C, C);
    cin >> D;
    strcpy(D, D);
    for (int i = 0; i < sum; i++)
    {
        if (ship[i].type[0]==C[0] && ship[i].type[1] == C[1] && ship[i].type[2] == C[2] && ship[i].id == j && ship[i].membership==p->id)
        {
            if (!strcmp(D, "F"))
            {
                Board::forward(&ship[i]);
            }
            else if (!strcmp(D, "R"))
            {
                Board::forward(&ship[i]);
                int y = ship[i].front_y, x = ship[i].front_x;
                Board::right(&ship[i], y, x);
            }
            else if (!strcmp(D, "L"))
            {
                Board::forward(&ship[i]);
                int y = ship[i].front_y, x = ship[i].front_x;
                Board::left(&ship[i], y, x);
            }
        }
    }
}

void Board::forward(Entity* ship)
{
    if (ship->direction == 'N')
    {
        tabr[ship->front_y - 1][ship->front_x] = ship;
        tabr[ship->front_y - 1 + ship->size][ship->front_x] = nullptr;
        tab[ship->front_y - 1][ship->front_x] = ship->body[0];
        tab[ship->front_y - 1 + ship->size][ship->front_x] = ' ';
        ship->front_y -= 1;
    }
    if (ship->direction == 'E')
    {
        tabr[ship->front_y][ship->front_x+1] = ship;
        tabr[ship->front_y][ship->front_x+1-ship->size] = nullptr;
        tab[ship->front_y][ship->front_x+1] = ship->body[0];
        tab[ship->front_y][ship->front_x+1-ship->size] = ' ';
        ship->front_x += 1;
    }
    if (ship->direction == 'S')
    {
        tabr[ship->front_y + 1][ship->front_x] = ship;
        tabr[ship->front_y + 1 - ship->size][ship->front_x] = nullptr;
        tab[ship->front_y + 1][ship->front_x] = ship->body[0];
        tab[ship->front_y + 1 - ship->size][ship->front_x] = ' ';
        ship->front_y += 1;
    }
    if (ship->direction == 'W')
    {
        tabr[ship->front_y][ship->front_x - 1] = ship;
        tabr[ship->front_y][ship->front_x - 1 + ship->size] = nullptr;
        tab[ship->front_y][ship->front_x - 1] = ship->body[0];
        tab[ship->front_y][ship->front_x - 1 + ship->size] = ' ';
        ship->front_x -= 1;
    }
}

void Board::right(Entity* ship, int y, int x)
{
    if (ship->direction == 'N')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y + a][x] = nullptr;
            tab[y + a][x] = ' ';
            tabr[y][x + a] = ship;
            tab[y][x + a] = ship->body[0];
        }
        ship->front_x += ship->size - 1;
        ship->direction = 'E';
    }
    else if (ship->direction == 'E')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y][x - a] = nullptr;
            tab[y][x - a] = ' ';
            tabr[y + a][x] = ship;
            tab[y + a][x] = ship->body[0];
        }
        ship->front_y += ship->size - 1;
        ship->direction = 'S';
    }
    else if (ship->direction == 'S')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y - a][x] = nullptr;
            tab[y - a][x] = ' ';
            tabr[y][x - a] = ship;
            tab[y][x - a] = ship->body[0];
        }
        ship->front_x -= ship->size + 1;
        ship->direction = 'W';
    }
    else if (ship->direction == 'W')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y][x + a] = nullptr;
            tab[y][x + a] = ' ';
            tabr[y - a][x] = ship;
            tab[y - a][x] = ship->body[0];
        }
        ship->front_y -= ship->size + 1;
        ship->direction = 'N';
    }
}

void Board::left(Entity* ship, int y, int x)
{
    if (ship->direction == 'N')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y + a][x] = nullptr;
            tab[y + a][x] = ' ';
            tabr[y][x - a] = ship;
            tab[y][x - a] = ship->body[0];
        }
        ship->front_x -= ship->size + 1;
        ship->direction = 'W';
    }
    else if (ship->direction == 'E')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y][x - a] = nullptr;
            tab[y][x - a] = ' ';
            tabr[y - a][x] = ship;
            tab[y - a][x] = ship->body[0];
        }
        ship->front_y -= ship->size + 1;
        ship->direction = 'N';
    }
    else if (ship->direction == 'S')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y - a][x] = nullptr;
            tab[y - a][x] = ' ';
            tabr[y][x + a] = ship;
            tab[y][x + a] = ship->body[0];
        }
        ship->front_x += ship->size - 1;
        ship->direction = 'E';
    }
    else if (ship->direction == 'W')
    {
        for (int a = 1; a < ship->size; a++)
        {
            tabr[y][x + a] = nullptr;
            tab[y][x + a] = ' ';
            tabr[y + a][x] = ship;
            tab[y + a][x] = ship->body[0];
        }
        ship->front_y += ship->size - 1;
        ship->direction = 'S';
    }
}

Board::~Board()
{
    for (int i = 0; i < height; i++)
    {
        *tabr[i] = nullptr;
        delete[] tab[i];
        delete[] * tabr[i];
    }
    delete[] tab;
    delete[] * tabr;
}