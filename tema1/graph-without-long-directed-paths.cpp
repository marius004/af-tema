#include <iostream>
#include <vector>

using namespace std;

bool isBipartite(int node, int color, vector<short>& colors, vector<vector<int>>& graph) {
    colors[node] = color;

    bool ans = true;
    for (int neighbor : graph[node]) {
        if (colors[neighbor] == -1)
            ans &= isBipartite(neighbor, 1 ^ color, colors, graph);
        ans &= (colors[neighbor] != colors[node]);

        if (!ans) return false;
    }

    return ans;
}

int main() {
    int n, m; 
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    vector<vector<int>> graph(n);

    for (auto& edge : edges) {
        cin >> edge.first >> edge.second;
        edge.first--; edge.second--;

        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }

    vector<short> colors(n, -1);
    if (!isBipartite(0, 0, colors, graph)) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";
    for (const auto edge : edges)
        cout << (colors[edge.first] < colors[edge.second]);
    
    return 0;
}