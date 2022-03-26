struct Pos { //basic class for cord
    int x;
    int y;
    Pos();
    Pos(int x, int y);
    bool operator == (Pos p);
    bool operator != (Pos p);
    Pos operator + (Pos p);
    operator bool() const;
};

struct Step {
    Pos from;
    Pos to;
    Step(Pos f, Pos t);
};

struct SChecker {  //basic struct for checker
    int Color;
    bool King;
    bool Fake;
    SChecker(int player);
    SChecker();

    bool Enemy(const SChecker& x);
};
