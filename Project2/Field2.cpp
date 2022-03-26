#include "Field.h"

long long SField::Goodness(int player) {  // console mode(old versoin)
    long long ans = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (Field[i][j].Color != 0) {
                long long tmp = 0;
                const long long num = (1 << 20);
                int NX = 0;
                if (at(i, j).Color == 1) NX = 7;
                if (at(i, j).King) {
                    tmp += 4200 * num;
                }
                else {
                    tmp += 1488 * num;
                    for (int i = 0; i < abs(i - NX); i++)
                        tmp -= (num >> i);
                }
                if (Field[i][j].Color == player) {
                    ans += tmp;
                }
                else {
                    ans -= tmp;
                }
            }
    return ans + rand() % 42;
}

/*void SField::ShowConsole() {
    for (int i = 0; i < 8; i++) {
        cout << ' ' << 8 - i;
        for (int j = 0; j < 8; j++) {
            cout << '|';
            if ((i + j) % 2 == 0) {
                cout << " ";
                continue;
            }
            if (Field[i][j].Color == 0) cout << ".";
            if (Field[i][j].Color == 1) {
                if (!Field[i][j].King) cout << "x";
                if (Field[i][j].King) cout << "X";
            }
            if (Field[i][j].Color == 2) {
                if (!Field[i][j].King) cout << "o";
                if (Field[i][j].King) cout << "O";
            }
        }
        cout << '|';
        cout << '\n';
    }

    cout << ' ' << ' ' << ' ';
    for (int j = 0; j < 8; j++) {
        cout << (char)(j + 'a') << ' ';
    }
    cout << std::endl;
}*/

void SField::ClearFake() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (Field[i][j].Fake)
                Field[i][j] = SChecker();
}