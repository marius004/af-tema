// https://www.infoarena.ro/problema/lanterna

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("lanterna.in");
ofstream g("lanterna.out");

struct idk { int node, time, watts; };

const int NMAX = 51;
const int KMAX = 1001;
const int INF = (1 << 30);

int N, K, M, dp[NMAX][KMAX];
bool friendly[NMAX];
vector < idk > G[NMAX];

int bellmanFord(const int& ENERGY) {

    for(int i = 1;i <= N;++i)
        for(int j = 0;j <= ENERGY;++j)
            dp[i][j] = INF;

    vector < vector < bool > > inQueue(N + 1, vector < bool >(ENERGY + 1, false));
    queue < pair < int, int > > q;

    q.push({ 1, ENERGY }); /// ENERGY == WATTS
    dp[1][ENERGY] = 0; /// time
    inQueue[1][ENERGY] = true;

    while(!q.empty()) {

        const auto& el = q.front();
        inQueue[el.first][el.second] = false;
        q.pop();

        for(auto& x : G[el.first]) {

           int r = el.second - x.watts;

           if(r < 0)
               continue;

           if(friendly[x.node]) // if I can recharge the batteries
               r = ENERGY;

           if(dp[x.node][r] > dp[el.first][el.second] + x.time) {

               dp[x.node][r] = dp[el.first][el.second] + x.time;

               if(!inQueue[x.node][r]) {
                   inQueue[x.node][r] = true;
                   q.push({ x.node, r });
               }
           }
        }
    }

    int sol{ INF };
    for(int j = 0;j <= ENERGY;++j)
        sol = min(sol, dp[N][j]);

    return sol;
}

int main() {

    f >> N >> K;

    for(int i = 1;i <= N;++i)
        f >> friendly[i];

    f >> M;

    while(M--) {

        int u, v, t, w;
        f >> u >> v >> t >> w;

        G[u].push_back({ v, t, w });
        G[v].push_back({ u, t, w });
    }

    int sol = bellmanFord(K);

    int left = 1, right = K, index = K;

    while(left <= right) {

        int mid = (left + right) / 2;

        if(bellmanFord(mid) == sol) {
            right = mid - 1;
            index = mid;
        } else
            left = mid + 1;
    }

    g << sol << ' ' << index;

    return 0;
}