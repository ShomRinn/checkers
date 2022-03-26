#include "Field.h"

SField::SField() {
    Field = new SChecker * [8];
    for (int i = 0; i < 8; i++)
        Field[i] = new SChecker[8];

    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 8; j++)
            if ((i + j) % 2 == 1)
                Field[i][j] = SChecker(1);

    for (int i = 5; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((i + j) % 2 == 1)
                Field[i][j] = SChecker(2);
    
}

SField::SField(const SField& base) {
    Field = new SChecker * [8];
    for (int i = 0; i < 8; i++)
        Field[i] = new SChecker[8];

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            Field[i][j] = base[i][j];
}

SField::~SField() {
    for (int i = 0; i < 8; i++)
        delete[] Field[i];
    delete[] Field;
}

SField& SField::operator = (const SField& base) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            Field[i][j] = base[i][j];
    return *this;
}

SChecker& SField::operator [] (Pos p) const {
    return Field[p.x][p.y];
}
SChecker& SField::at(Pos p) const {
    return Field[p.x][p.y];
}
SChecker* SField::operator [] (int index) const {
    return Field[index];
}
SChecker& SField::at(int i, int j) const {
    return Field[i][j];
}

bool SField::IsFree(Pos p) {  // Can cheacker move? check
    if (p.x < 0 || 8 <= p.x) return false;
    if (p.y < 0 || 8 <= p.y) return false;
    if (at(p).Color == 0) return true;
    return false;
}
bool SField::IsOkay(Pos p) {
    if (p.x < 0 || 8 <= p.x) return false;
    if (p.y < 0 || 8 <= p.y) return false;
    return true;
}

void SField::Move(Pos p, Pos pNew) {  //movement
    if (at(p).Color == 0) throw 42;
    if (abs(pNew.x - p.x) != abs(pNew.y - p.y)) throw 42;

    int cx = 1, cy = 1;
    if (pNew.x < p.x) cx = -1;
    if (pNew.y < p.y) cy = -1;
    at(pNew) = at(p);
    for (int d = 0; d < abs(pNew.x - p.x); d++)
    {
        if (at(p + Pos(d * cx, d * cy)).Color != 0)
        {
            at(p) = SChecker();
            at(p + Pos(d * cx, d * cy)).Color = 1 + 2 - at(p + Pos(d * cx, d * cy)).Color;
            at(p + Pos(d * cx, d * cy)).Fake = true;
        }
            
    }
    int NX = 0;
    if (at(pNew).Color == 1) NX = 7;
    if (pNew.x == NX) {
        at(pNew).King = true;
    }
}

vector<Pos> SField::CheckerAttack(Pos p) { // Can cheacker attack? check
    vector<Pos> moves;
    if (!at(p).King) {
        for (int dx = -1; dx <= 1; dx += 2)
            for (int dy = -1; dy <= 1; dy += 2)
                if (IsFree(p + Pos(dx * 2, dy * 2)))
                    if (at(p).Enemy(at(p + Pos(dx, dy))))
                        moves.push_back(p + Pos(dx * 2, dy * 2));
    }
    else {
        for (int cx = -1; cx <= 1; cx += 2)
            for (int cy = -1; cy <= 1; cy += 2)
                for (int d = 1; d <= 8; d++)
                    if (IsOkay(p + Pos(d * cx, d * cy)))
                        if (at(p + Pos(d * cx, d * cy)).Color != 0) {
                            if (at(p).Enemy(at(p + Pos(d * cx, d * cy))))
                                if (IsFree(p + Pos((d + 1) * cx, (d + 1) * cy)))
                                    for (int t = 1; t <= 8; t++) {
                                        if (IsFree(p + Pos((d + t) * cx, (d + t) * cy)))
                                            moves.push_back(p + Pos((d + t) * cx, (d + t) * cy));
                                        else
                                            break;
                                    }
                            break;
                        }
    }
    return moves;
}
bool SField::CanCheckerAttack(Pos p) {  //attack
    return (CheckerAttack(p).size() > 0);
}
bool SField::CanCheckerAttack(Pos p, Pos pNew) {
    vector<Pos> moves = CheckerAttack(p);
    for (size_t i = 0; i < moves.size(); i++)
        if (moves[i] == pNew)
            return true;
    return false;
}
bool SField::CanPlayerAttack(int player) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (at(i, j).Color == player)
                if (CanCheckerAttack(Pos(i, j)))
                    return true;
    return false;
}

vector<Pos> SField::CheckerMove(Pos p) {
    vector<Pos> moves;
    if (!at(p).King) {
        int dx = 1;
        if (at(p).Color == 2) dx = -1;
        for (int dy = -1; dy <= 1; dy += 2)
            if (IsFree(p + Pos(dx, dy)))
                moves.push_back(p + Pos(dx, dy));
    }
    else {
        for (int cx = -1; cx <= 1; cx += 2)
            for (int cy = -1; cy <= 1; cy += 2)
                for (int d = 1; d <= 8; d++) {
                    if (IsFree(p + Pos(d * cx, d * cy)))
                        moves.push_back(p + Pos(d * cx, d * cy));
                    else
                        break;
                }
    }
    return moves;
}
bool SField::CanCheckerMove(Pos p) {
    return (CheckerMove(p).size() > 0);
}
bool SField::CanCheckerMove(Pos p, Pos pNew) {
    vector<Pos> moves = CheckerMove(p);
    for (size_t i = 0; i < moves.size(); i++)
        if (moves[i] == pNew)
            return true;
    return false;
}
bool SField::CanPlayerMove(int player) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (at(i, j).Color == player)
                if (CanCheckerMove(Pos(i, j)))
                    return true;
    return false;
}

vector<Step> SField::AllMoves(int player) {
    vector<Step> moves;
    if (CanPlayerAttack(player)) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (at(i, j).Color == player)
                    if (CanCheckerAttack(Pos(i, j))) {
                        vector<Pos> tmp = CheckerAttack(Pos(i, j));
                        for (int i = 0; i < tmp.size(); i++)
                            moves.push_back(Step(Pos(i, j), tmp[i]));
                    }
    }
    else {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (at(i, j).Color == player)
                    if (CanCheckerMove(Pos(i, j))) {
                        vector<Pos> tmp = CheckerMove(Pos(i, j));
                        for (int i = 0; i < tmp.size(); i++)
                            moves.push_back(Step(Pos(i, j), tmp[i]));
                    }
    }
    return moves;
}
vector<Pos> SField::AllCheckers(int player) {
    vector<Pos> checkers;
    if (CanPlayerAttack(player)) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (at(i, j).Color == player)
                    if (CanCheckerAttack(Pos(i, j))) {
                        checkers.push_back(Pos(i, j));
                    }
    }
    else {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (at(i, j).Color == player)
                    if (CanCheckerMove(Pos(i, j))) {
                        checkers.push_back(Pos(i, j));
                    }
    }
    return checkers;
}
bool SField::CanPlayerUseChecker(int player, Pos p) {
    vector<Pos> checks = AllCheckers(player);
    for (size_t i = 0; i < checks.size(); i++)
        if (checks[i] == p)
            return true;
    return false;
}
