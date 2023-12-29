// https://infoarena.ro/job_detail/2663051?action=view-source

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("ghizi.in");
ofstream g("ghizi.out");

const int NMAX = 105;

int N, K, Capacity[NMAX][NMAX], Flow[NMAX][NMAX], parent[NMAX];
pair < int, int > date[5005];
bool vis[NMAX];
vector < int > G[NMAX];

bool bfs() {

    for(int i = 0;i <= 101;++i) vis[i] = false, parent[i] = 0;

    queue < int > q;

    vis[0] = true;
    q.push(0);

    while(!q.empty()) {

        const int node = q.front();
        q.pop();

        for(int neighbor : G[node]) {

            if(!vis[neighbor] && Capacity[node][neighbor] > Flow[node][neighbor]) {

                vis[neighbor] = true;

                parent[neighbor] = node;
                q.push(neighbor);
            }
        }
    }

    return vis[101];
}

int main() {

    f >> N >> K;

    G[0].push_back(1);
    G[1].push_back(0);

    Capacity[0][1] = K;

    for(int i = 1;i <= N;++i) {
        int x, y;
        f >> x >> y;

        x++; y++;

        G[x].push_back(y);
        G[y].push_back(x);

        Capacity[x][y]++;
        date[i] = { x, y };
    }

    while(bfs()) {

        for(const int& node : G[101]) {

            int u = node;

            if(vis[u] && Capacity[u][101] > Flow[u][101]) {

                int minnEdge = Capacity[u][101] - Flow[u][101];

                while(u != 0) {
                    minnEdge = min(minnEdge, Capacity[ parent[u] ][u] - Flow[ parent[u] ][u]);
                    u = parent[u];
                }

                u = node;
                Flow[u][101] += minnEdge;
                Flow[101][u] -= minnEdge;

                while(u != 0) {
                    Flow[ parent[u] ][u] += minnEdge;
                    Flow[u][ parent[u] ] -= minnEdge;
                    u = parent[u];
                }
            }
        }
    }

    vector < int > sol;
    for(int i = 1;i <= N;++i) {
        if(Flow[ date[i].first ][ date[i].second ]) {
            sol.push_back(i);
            Flow[ date[i].first ][ date[i].second ]--;
        }
    }

    g << (int)sol.size() << '\n';
    for(int it : sol)
        g << it << ' ';

    return 0;
}