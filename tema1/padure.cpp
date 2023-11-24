#include <iostream>
#include <fstream>
#include <bitset>
#include <deque>

using namespace std;

ifstream f("padure.in");
ofstream g("padure.out");

const int NMAX = 1001;
const int INF = (1 << 26);

int N, M, sol = INF, Cost[NMAX][NMAX];
short grid[NMAX][NMAX];
pair < int , int > StartCoord, EndCoord;
deque < pair < int , int > > dq;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void Read() {

    f >> N >> M;
    f >> StartCoord.first >> StartCoord.second;
    f >> EndCoord.first >> EndCoord.second;

    for(int i = 1;i <= N;++i)
        for(int j = 1;j <= M;++j)
            f >> grid[i][j], Cost[i][j] = INF;
}

void Solve() {

    Cost[StartCoord.first][StartCoord.second] = 0;
    dq.push_back(StartCoord);

    auto isValidCoordonate = [&](const int& x,const int& y) -> bool {
        return x >= 1 && x <= N && y >= 1 && y <= M;
    };

    while(!dq.empty()) {

        auto el = dq.front();
        dq.pop_front();

        for(int dir = 0; dir < 4; ++dir) {

            int new_i = el.first  + dx[dir];
            int new_j = el.second + dy[dir];

            if(isValidCoordonate(new_i, new_j)) {

                if(grid[el.first][el.second] == grid[new_i][new_j]) {
                    if(Cost[el.first][el.second] < Cost[new_i][new_j]) {
                        dq.push_front({new_i, new_j});
                        Cost[new_i][new_j] = Cost[el.first][el.second];
                    }
                }else {
                    if(Cost[el.first][el.second] + 1 < Cost[new_i][new_j]) {
                        dq.push_back({new_i, new_j});
                        Cost[new_i][new_j] = Cost[el.first][el.second] + 1;
                    }
                }
            }
        }
    }

    g << Cost[EndCoord.first][EndCoord.second];
}


int main() {

    Read();
    Solve();

    return 0;
}
