#include "Field.h"
class Checkers {
protected:
    SField Field;
    bool Move(int player, Pos p, Pos pNew);
    static vector< vector<Step> > AllFutureStates(vector<SField>& allFutureStates, SField& base, int player);  // AI check movement?
public:
    bool EndGame(int player);
    bool Mirror = false; //side
    void SHOW(); //draw map
    void MOVE(Pos p, Pos pNew); //movement
    void SELECT(Pos p);  //make checkers select
    void MakeAutoMove(int player, int DeepOfTurns = 2); // AI movement
};