#include "Structs.h"

Pos::Pos() {
    this->x = -1;
    this->y = -1;
}

Pos::Pos(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Pos::operator == (Pos p)
{
    return p.x == this->x && p.y == this->y;
}

bool Pos::operator != (Pos p) 
{
    return p.x != this->x || p.y != this->y;
}

Pos Pos::operator + (Pos p) {
    return Pos(this->x + p.x, this->y + p.y);
}

Pos::operator bool() const
{
    if (x < 0 || 8 <= x) return false;
    if (y < 0 || 8 <= y) return false;
    return true;
}

// ------------------------------------------

Step::Step(Pos f, Pos t) {
    from = f;
    to = t;
}

// ------------------------------------------

SChecker::SChecker(int player) {
    Color = player;
    King = false;
    Fake = false;
}
SChecker::SChecker() {
    Color = 0;
    King = false;
    Fake = false;
}

bool SChecker::Enemy(const SChecker& x) {
    if (x.Color == 0) return false;
    if (this->Color == 0) return false;
    if (x.Color != this->Color) return true;
    return false;
}
