#include "Checkers.h"

bool Checkers::Move(int player, Pos p, Pos pNew) { //player checkers movement
    if (Field[p].Color != player) return false;
    if (!Field.IsFree(pNew)) return false;
    if (Field.CanCheckerAttack(p, pNew)) {
        MOVE(p,pNew);
        Field.Move(p, pNew);
        return true;
    }
    if (Field.CanPlayerAttack(player)) return false;
    if (Field.CanCheckerMove(p, pNew)) {
        MOVE(p, pNew);
        Field.Move(p, pNew);
        return true;
    }
    return false;
}

vector< vector<Step> > Checkers::AllFutureStates(vector<SField>& allFutureStates, SField& base, int player) {  
    vector<SField> states;
    vector< vector<Step> > history;
    vector<Pos> checks = base.AllCheckers(player);

    if (base.CanPlayerAttack(player)) {
        for (size_t i = 0; i < checks.size(); i++) {
            vector<Pos> moves = base.CheckerAttack(checks[i]);
            if (moves.size() == 0) throw 42;
            for (size_t j = 0; j < moves.size(); j++) {
                SField tmpField(base);
                tmpField.Move(checks[i], moves[j]);
                states.push_back(tmpField);
                vector<Step> tmp;
                tmp.push_back(Step(checks[i], moves[j]));
                history.push_back(tmp);
            }
        }
        for (size_t i = 0; i < states.size(); i++) {
            Pos p = history[i][history[i].size() - 1].to;
            if (states[i].CanCheckerAttack(p)) {
                vector<Pos> moves = states[i].CheckerAttack(p);
                for (size_t j = 0; j < moves.size(); j++) {
                    SField tmpField(states[i]);
                    tmpField.Move(p, moves[j]);
                    states.push_back(tmpField);
                    vector<Step> tmp(history[i]);
                    tmp.push_back(Step(p, moves[j]));
                    history.push_back(tmp);
                }
                states.erase(states.begin() + i);
                history.erase(history.begin() + i);
                i--;
            }
        }
    }
    else {
        for (size_t i = 0; i < checks.size(); i++) {
            vector<Pos> tmp = base.CheckerMove(checks[i]);
            if (tmp.size() == 0) throw 42;
            for (size_t j = 0; j < tmp.size(); j++) {
                SField fld(base);
                fld.Move(checks[i], tmp[j]);
                states.push_back(fld);
                vector<Step> hist;
                hist.push_back(Step(checks[i], tmp[j]));
                history.push_back(hist);
            }
        }
    }
    for (size_t i = 0; i < states.size(); i++)
        states[i].ClearFake();
    allFutureStates = states;
    return history;
}

bool Checkers::EndGame(int player) {
    return (Field.AllMoves(player).size() == 0);
}

void Checkers::MakeAutoMove(int player, int DeepOfTurns) {  //Movement

    struct TreeVertex {
        SField fld;
        int player;

        int deep;
        long long goods;

        TreeVertex* prev;
        vector<TreeVertex> next;
        vector< vector<Step> > hist;

        int BasePlayer() {
            if (prev == nullptr)
                return this->player;
            else
                return prev->BasePlayer();
        }
        TreeVertex(const SField& base, int plr, TreeVertex* prv = nullptr, int dp = 0) {
            fld = base;
            player = plr;
            prev = prv;
            deep = dp;
        }
        void Create() {      //Creation
            if (next.size() != 0) {
                throw;
            }
            vector<SField> tmp;
            hist = AllFutureStates(tmp, fld, player);
            for (size_t i = 0; i < tmp.size(); i++)
                next.push_back(TreeVertex(tmp[i], 1 + 2 - player, this, deep + 1));
        }
        void dfs(int TurnDeep) {
            if (deep < TurnDeep * 2) {
                this->Create();
                if (next.size() == 0) {
                    goods = fld.Goodness(BasePlayer());
                    return;
                }
                for (size_t i = 0; i < next.size(); i++)
                    next[i].dfs(TurnDeep);
                goods = next[0].goods;
                for (size_t i = 0; i < next.size(); i++) {
                    if (deep % 2 == 0) {
                        if (goods < next[i].goods)
                            goods = next[i].goods;
                    }
                    else {
                        if (goods > next[i].goods)
                            goods = next[i].goods;
                    }
                }
            }
            if (deep == TurnDeep * 2) {
                goods = fld.Goodness(BasePlayer());
            }
        }
        size_t WhatToDo() {  //How do you do diadia Zhora?
            if (prev != nullptr)
                throw;
            for (size_t i = 0; i < next.size(); i++)
                if (next[i].goods == goods)
                    return i;
                else if (next[i].goods > goods)
                    throw;
            throw;
        }
    };

    TreeVertex calc(Field, player);
    calc.dfs(DeepOfTurns);

    size_t ind = calc.WhatToDo();
    if (calc.hist.size() <= ind) throw 42;
    for (size_t i = 0; i < calc.hist[ind].size(); i++)
    {
        if (!Move(player, calc.hist[ind][i].from, calc.hist[ind][i].to))
            throw;
        SHOW();
    }
    Field.ClearFake();
    SHOW();
}
