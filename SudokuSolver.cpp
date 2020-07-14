#include <bits/stdc++.h>
using namespace std;

const int r = 9;
const int c = 9;
const int inf = 1e9;

int board[r + 1][c + 1];
pair <int,int> start[r + 1][c + 1];

// for each block of 3 x 3 it calculates the start or top left cell id
void calc_start() {
    for (int i = 1; i <= r; i += 3) {
        for (int j = 1; j <= c; j += 3) {
            for (int k = i; k <= i + 2; k++) {
                for (int l = j; l <= j + 2; l++) {
                    start[k][l] = make_pair(i, j);
                }
            }
        }
    }
}

// for any given cell it calculated the available digits that we may use
vector <int> get_available(int cr, int cc) {
    vector <int> have(10, 0);
    vector <int> ret;
    for (int j = 1; j <= c; j++) have[board[cr][j]]++;
    for (int i = 1; i <= r; i++) have[board[i][cc]]++;
    pair < int, int > p = start[cr][cc];
    for (int k = p.first; k <= p.first + 2; k++) {
        for (int l = p.second; l <= p.second + 2; l++) {
            have[board[k][l]]++;
        }
    }
    for (int i = 1; i <= 9; i++) {
        if (have[i] == 0) ret.push_back(i);
    }
    return ret;
}

// checks if the current configuration has any conflict or not!
bool conflict() {
    for (int i = 1; i <= r; i++) {
        vector <int> cnt(10, 0);
        for (int j = 1; j <= c; j++) {
            cnt[board[i][j]]++;
            if (board[i][j] != 0 && cnt[board[i][j]] > 1) return true;
        }
    }
    for (int i = 1; i <= c; i++) {
        vector < int > cnt(10, 0);
        for (int j = 1; j <= r; j++) {
            cnt[board[j][i]]++;
            if (board[j][i] != 0 && cnt[board[j][i]] > 1) return true;
        }
    }
    for (int i = 1; i <= r; i += 3) {
        for (int j = 1; j <= c; j += 3) {
            vector <int> cnt(10, 0);
            for (int k = i; k <= i + 2; k++) {
                for (int l = j; l <= j + 2; l++) {
                    cnt[board[k][l]]++;
                    if (board[k][l] != 0 && cnt[board[k][l]] > 1) return true;
                }
            }
        }
    }
    return false;
}

// get the current best cell to put a value in it based on the minimum available options for it
pair <int,int> get_the_best() {
    pair <int,int> ret = make_pair(-1, -1);
    int mn = inf;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (board[i][j] != 0) continue;
            vector <int> can = get_available(i, j);
            if (can.size() < mn) mn = can.size(), ret = make_pair(i, j);
        }
    }
    return ret;
}

// recursive solver function that takes the number of empty cell available
bool sudoku_solver(int rem) {
    if (rem == 0) return conflict() ? false : true;
    bool ret = false;
    pair <int,int> p = get_the_best();
    int x = p.first, y = p.second;
    if (x == -1 && y == -1) return true;
    if (board[x][y] != 0) ret |= sudoku_solver(rem);
    else {
        vector <int> can = get_available(x, y);
        for (int i = 0; i < (int)can.size(); i++) {
            board[x][y] = can[i];
            ret |= sudoku_solver(rem - 1);
            if (ret) break;
            else board[x][y] = 0;
        }
    }
    return ret;
}

int main() {
    calc_start();
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        int cnt = 0;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                scanf("%d", & board[i][j]);
                if (board[i][j] == 0) cnt++;
            }
        }
        printf("Case #%d\n", tc);
        if (sudoku_solver(cnt)) {
            for (int i = 1; i <= r; i++) {
                for (int j = 1; j <= c; j++) {
                    printf("%d", board[i][j]);
                    if (j < c) printf(" ");
                }
                printf("\n");
            }
        } else printf("No solution\n");
    }
    return 0;
}

