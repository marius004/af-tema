// https://www.infoarena.ro/problema/dragoni

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("dragoni.in");
ofstream g("dragoni.out");

const long long NMAX = 801;
const long long INF = (1 << 30);

long long type, n, m, dragonDistance[NMAX], dp[NMAX][NMAX];
vector < pair < long, long > > G[NMAX];

// dp[i][j] - costul ca sa ajung din 1 in i cu dragonul j
// initializare dp[1][1] = 0

void read() {

    f >> type >> n >> m;

    for(int i = 1;i <= n;++i)
        f >> dragonDistance[i];

    while(m--) {
        long long x, y, cost;
        f >> x >> y >> cost;
        G[x].push_back( { y, cost } );
        G[y].push_back( { x, cost } );
    }
}

long long getMaxDragonDistance(const long long& startNode) {

    long long ans{ dragonDistance[1] };
    queue < long long > q;
    vector < bool > beenThere(n + 1, false);

    beenThere[startNode] = true;
    q.push(startNode);

    while(!q.empty()) {

        const long long node = q.front();
        q.pop();

        for(pair < long long, long long > neighbour : G[node]) {
            if(!beenThere[neighbour.first] && dragonDistance[1] >= neighbour.second) {
                ans = max(ans, dragonDistance[neighbour.first]);
                beenThere[neighbour.first] = true;
                q.push(neighbour.first);
            }
        }
    }

    return ans;
}

struct element {
    long long node, dragon, cost;
};

struct Pq_Compartor {
    bool operator()(const element& a,const element& b) {
        return a.cost > b.cost;
    }
};

void dijkstra() {

    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            dp[i][j] = INF;

    dp[1][1] = 0;

    priority_queue < element, vector < element > , Pq_Compartor > pq;
    pq.push( { 1, 1, 0 } );

    while(!pq.empty()) {

        const long long node = pq.top().node;
        const long long dragon = pq.top().dragon;
        const long long cost = pq.top().cost;
        pq.pop();

        if(dp[node][dragon] == cost) {
            for (pair<long long, long long> neighbour : G[node]) {
                // we won't change the dragon
                if(dragonDistance[dragon] >= neighbour.second &&
                   dp[node][dragon] + neighbour.second < dp[neighbour.first][dragon]) {
                    dp[neighbour.first][dragon] = dp[node][dragon] + neighbour.second;
                    pq.push( { neighbour.first, dragon, dp[neighbour.first][dragon] } );
                }
                // we'll change the dragon
                if(dragonDistance[dragon] >= neighbour.second &&
                   dp[node][dragon] + neighbour.second < dp[neighbour.first][neighbour.first]) {
                    dp[neighbour.first][neighbour.first] = dp[node][dragon] + neighbour.second;
                    pq.push( { neighbour.first, neighbour.first, dp[neighbour.first][neighbour.first] });
                }
            }
        }
    }
}

void solve() {
    if (type == 1) {
        g << getMaxDragonDistance(1);
    } else {
        dijkstra();

        long long ans{ dp[n][1] };
        for(int i = 2;i <= n;++i)
            ans = min(ans, dp[n][i]);

        g << ans;
    }
}

int main() {

    read();
    solve();

    return 0;
}