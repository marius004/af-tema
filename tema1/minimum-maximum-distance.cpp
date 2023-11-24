// https://codeforces.com/contest/1881/problem/F
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue> 

using namespace std;
using Graph = vector<vector<int>>;

vector<int> bfs(int source, const Graph& graph) {
    vector<int> dist(graph.size(), -1);
    queue<int> q;

    dist[source] = 0;
    q.push(source);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = 1 + dist[u]; 
                q.push(v);
            }
        }
    }

    return dist;
}

int solve(const Graph& graph, const vector<int>& marked) {
    if (marked.size() < 2) {
        return 0;
    }

    auto dist = bfs(marked[0], graph);
    int diam = 0, farthest = -1;
    for (const int node : marked) {
        if (dist[node] > diam) {
            diam = dist[node];
            farthest = node; 
        }
    }

    dist = bfs(farthest, graph);
    for (const int node : marked) {
        diam = max(diam, dist[node]);
    }

    return (1 + diam) / 2;
}

int main() {
    int t; cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> marked(k);
        for (int &vertex : marked)
            cin >> vertex;
        
        vector<vector<int>> graph(n + 1);
        for (int i = 0;i < n - 1;++i) {
            int u, v;
            cin >> u >> v;

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        cout << solve(graph, marked) << '\n';
    }

    return 0;
}