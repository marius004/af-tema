// https://www.infoarena.ro/problema/patrol2

#include <fstream>
#include <vector> 
#include <queue>

using namespace std; 
using Graph = vector<vector<int>>;

ifstream fin("patrol2.in");
ofstream fout("patrol2.out");

// lcm(1,2,3,4,5,6,7)
static constexpr int PATROLS_CYCLE = 420; 


int main() {
    int n, m, k; 
    fin >> n >> m >> k;

    Graph graph(n);
    for (int i = 0;i < n;++i) {
        graph[i].push_back(i);
    }

    for (int i = 0;i < m; ++i) {
        int u, v;
        fin >> u >> v; 

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<vector<int>> patrols(k);
    for (int i = 0; i < k; ++i) {
        int count; 
        fin >> count; 

        for (int j = 0;j < count; ++j) {
            int u; fin >> u; 
            patrols[i].push_back(u);
        }
    }

    vector<vector<int>> dist(n, vector<int>(PATROLS_CYCLE, (1 << 30)));
    for (int i = 0;i < k; ++i) {
        for (int j = 0;j < patrols[i].size(); ++j) {
            for (int time = j;time < PATROLS_CYCLE;time += patrols[i].size())
                dist[patrols[i][j]][time] = -1;
        }
    }

    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));

    dist[0][0] = 0;
    while (!q.empty()) {
        int node = q.front().first;
        int cost = q.front().second;
        q.pop(); 

        for (const auto& neighbor : graph[node]) {
            int neighborCost = (1 + cost) % PATROLS_CYCLE;
            if (dist[neighbor][neighborCost] != -1 && dist[neighbor][neighborCost] > 1 + dist[node][cost]) {
                dist[neighbor][neighborCost] = 1 + dist[node][cost];
                q.push(make_pair(neighbor, neighborCost));
            }
        }
    }

    int ans = (1 << 30); 
    for (int cost = 0;cost < PATROLS_CYCLE; ++cost) {
        if (dist[n-1][cost] != -1)
            ans = min(ans, dist[n - 1][cost]);
    }

    fout << (ans == (1 << 30) ? -1 : ans);
    return 0;
}