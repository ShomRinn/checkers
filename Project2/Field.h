#include "Structs.h"
#include <math.h>
#include <vector>
#include <iostream>
using std::cout;
using std::vector;
struct SField {
    SChecker** Field;
    SField();
    SField(const SField& base);
    ~SField();
    SField& operator = (const SField& base);
    SChecker& operator [] (Pos p) const;
    SChecker& at(Pos p) const;
    SChecker* operator [] (int index) const;
    SChecker& at(int i, int j) const;
   // void ShowConsole(); //delete 
    bool IsFree(Pos p);  //for AI
    bool IsOkay(Pos p);
    void Move(Pos p, Pos pNew); // for you
    vector<Pos> CheckerAttack(Pos p);
    bool CanCheckerAttack(Pos p);
    bool CanCheckerAttack(Pos p, Pos pNew);
    bool CanPlayerAttack(int player);
    vector<Pos> CheckerMove(Pos p);
    bool CanCheckerMove(Pos p);
    bool CanCheckerMove(Pos p, Pos pNew);
    bool CanPlayerMove(int player);
    vector<Step> AllMoves(int player);
    vector<Pos> AllCheckers(int player);
    bool CanPlayerUseChecker(int player, Pos p);
    long long Goodness(int player);  //wtf?
    void ClearFake();
};