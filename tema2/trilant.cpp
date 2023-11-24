// https://www.infoarena.ro/problema/trilant

#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <climits>

using namespace std;
using WeightedGraph = vector<vector<pair<long, long>>>;

ifstream fin("trilant.in");
ofstream fout("trilant.out");

vector<vector<long long>> dijkstra(int n, const WeightedGraph& graph, int source) {
    vector<long long> dist(n + 1, (1LL << 42));
    vector<long long> parent(n + 1, -1);

    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<>> pq;

    pq.push({0, source});
    dist[source] = 0;

    for (;!pq.empty();) {
        auto cost = pq.top().first;
        auto node = pq.top().second;
        pq.pop();

        if (dist[node] != cost)
            continue;

        for (auto& it : graph[node]) {
            if (dist[it.first] > dist[node] + it.second) {
                dist[it.first] = dist[node] + it.second;
                parent[it.first] = node;
                pq.push({dist[it.first], it.first});
            }
        }
    }

    return {dist, parent};
}

int findX(const vector<long long>& distA,
          const vector<long long>& distB,
          const vector<long long>& distC) {

    long long minn = distA[1] + distB[1] + distC[1];
    int minnIndex = 1;

    for (int i = 2; i < distA.size(); ++i) {
        if (distA[i] + distB[i] + distC[i] < minn) {
            minn = distA[i] + distB[i] + distC[i];
            minnIndex = i;
        }
    }

    return minnIndex;
}

void printPath(int node, const vector<long long>& parent) {
    vector<int> path;
    while (node > 0) {
        path.push_back(node);
        node = parent[node];
    }

    fout << path.size() << ' ';
    for (int it : path) {
        fout << it << ' ';
    }

    fout << '\n';
}

int main() {
    int n, m;
    fin >> n >> m;

    int a, b, c;
    fin >> a >> b >> c;

    WeightedGraph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w;

        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }

    auto d1 = dijkstra(n, graph, a);
    auto d2 = dijkstra(n, graph, b);
    auto d3 = dijkstra(n, graph, c);

    int x = findX(d1[0], d2[0], d3[0]);

    fout << d1[0][x] + d2[0][x] + d3[0][x] << '\n';

    printPath(x, d1[1]);
    printPath(x, d2[1]);
    printPath(x, d3[1]);

    fin.close();
    fout.close();

    return 0;
}