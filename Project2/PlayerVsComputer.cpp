#include "PlayerVsComputer.h"

bool CheckersPvsC::Click(Pos Click) { //is action possible? checking
    if (Mirror) {
        Click.x = 7 - Click.x;
        Click.y = 7 - Click.y;
    }

    if (!CurChecker) {
        if (Field.CanPlayerUseChecker(GetPlayer(), Click)) {
            CurChecker = Click;
            SELECT(CurChecker);
        }
        return false;
    }

    if (CurChecker && !AlreadyAttack)
    {
        if (Click == CurChecker)
        {
            SHOW();
            CurChecker = Pos();
            return false;
        }
        if (Field.CanPlayerUseChecker(GetPlayer(), Click)) 
        {
            SHOW();
            CurChecker = Click;
            SELECT(CurChecker);
            return false;
        }
    }

    if (Field.CanCheckerAttack(CurChecker)) {
        if (!Field.CanCheckerAttack(CurChecker, Click)) {
            return false;
        }
        if (!Move(GetPlayer(), CurChecker, Click))
            throw;
        if (Field.CanCheckerAttack(Click)) {
            SHOW();
            CurChecker = Click;
            SELECT(CurChecker);
            AlreadyAttack = true;
            return false;
        }
    }
    else {
        if (!Field.CanCheckerMove(CurChecker, Click)) {
            return false;
        }
        if (!Move(GetPlayer(), CurChecker, Click))
            throw;
    }
    Field.ClearFake();
    SHOW();
    CurChecker = Pos();
    AlreadyAttack = false;

    if (EndGame(1 + 2 - GetPlayer())) {
        Winner = GetPlayer();
        return true;
    }

    MakeAutoMove(1 + 2 - GetPlayer());

    if (EndGame(GetPlayer())) {
        Winner = 1 + 2 - GetPlayer();
        return true;
    }

}