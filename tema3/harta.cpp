// https://www.infoarena.ro/job_detail/2662793?action=view-source

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("harta.in");
ofstream g("harta.out");

const int NMAX = 105;

int N, C[2 * NMAX][2 * NMAX], Flow[2 * NMAX][2 * NMAX], parent[2 * NMAX];
bool vis[2 * NMAX];
vector < int > G[2 * NMAX];

bool bfs() {

    for(int i = 1;i <= 2 * N + 1; ++i) vis[i] = false, parent[i] = 0;

    queue < int > q;
    q.push(0);
    vis[0] = true;

    while(!q.empty()) {

        const int node = q.front();
        q.pop();

        for(int neighbor : G[node]) {

            if(!vis[neighbor] && C[node][neighbor] > Flow[node][neighbor]) {

                vis[neighbor] = true;

                q.push(neighbor);
                parent[neighbor] = node;

                if(vis[2 * N + 1])
                    return true;
            }

        }
    }

    return vis[2 * N + 1];
}

int main() {

    f >> N;

    for(int i = 1;i <= N;++i) {
        int in, out;
        f >> in >> out;

        C[0][i] = in;
        C[i + N][2 * N + 1] = out;

        G[0].push_back(i);
        G[i].push_back(0);

        G[i + N].push_back(2 * N + 1);
        G[2 * N + 1].push_back(i + N);
    }

    for(int i = 1;i <= N;++i) {
        for(int j = N + 1; j <= 2 * N;++j) {
            if(j - N != i) {
                C[i][j] = 1;
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }

    while(bfs()) {

        for(int node : G[2 * N + 1]) {

            int u = node;
            if(vis[u] && C[u][2 * N + 1] > Flow[u][2 * N + 1]) {

                int minnEdge = C[u][2 * N + 1] - Flow[u][2 * N + 1];

                while(u != 0) {
                    minnEdge = min(minnEdge, C[parent[u]][u] - Flow[parent[u]][u]);
                    u = parent[u];
                }

                u = node;
                Flow[u][2 * N + 1] += minnEdge;
                Flow[2 * N + 1][u] -= minnEdge;

                while(u != 0) {
                    Flow[parent[u]][u] += minnEdge;
                    Flow[u][parent[u]] -= minnEdge;
                    u = parent[u];
                }

            }
        }
    }

    vector < pair < int, int >  > sol;
    for(int i = 1;i <= N;++i) {
        for(int j = N + 1;j <= 2 * N;++j) {
            if (i + N != j && Flow[i][j] == 1)
                sol.push_back({i, j - N});
        }
    }

    g << sol.size() << '\n';
    for(auto it : sol)
        g << it.first << ' ' << it.second << '\n';

    return 0;
}