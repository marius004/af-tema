// https://www.infoarena.ro/problema/camionas

#include <fstream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;
using WeightedGraph = vector<vector<pair<int, int>>>;

ifstream fin("camionas.in");
ofstream fout("camionas.out");

int dijkstra(int n, const WeightedGraph& graph, int source, int dest) {
    vector<int> dist(n + 1, INT32_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<>> pq;

    pq.push({0, source });
    dist[source] = 0;

    for(;!pq.empty();) {

        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(dist[node] != cost)
            continue;

        for(auto& it : graph[node]) {
            if(dist[it.first] > dist[node] + it.second) {
                dist[it.first] = dist[node] + it.second;
                pq.push({ dist[it.first], it.first });
            }
        }
    }

    return dist[dest] != INT32_MAX ? dist[dest] : -1;
}

int main() {
    int n, m, g;
    fin >> n >> m >> g;

    WeightedGraph graph(n + 1);
    for (int i = 0;i < m;++i) {
        int u, v, w;
        fin >> u >> v >> w;

        graph[u].push_back(make_pair(v, w < g));
        graph[v].push_back(make_pair(u, w < g));        
    }

    fout << dijkstra(n, graph, 1, n);

    fin.close();
    fout.close();

    return 0;
}