#include <fstream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("cc.in");
ofstream fout("cc.out");

struct Edge {
    int to, flow, capacity, cost, residual;
};

vector<vector<Edge>> network;

void add_edge(int u, int v, int capacity, int cost) {
    network[u].push_back({v, 0, capacity, cost, (int) network[v].size()});
    network[v].push_back({u, 0, 0, -cost, (int)network[u].size() - 1});
}

int min_cost_flow(int source, int sink) {
    int answer = 0;

    while (true) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(network.size(), INT_MAX);
        vector<pair<int, int>> from(network.size());

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            if (d > dist[u])
                continue;

            for (int i = 0; i < (int) network[u].size(); ++i) {
                int capacity = network[u][i].capacity;
                int flow = network[u][i].flow;
                int cost = network[u][i].cost;
                int v = network[u][i].to;

                if (capacity - flow > 0 && dist[u] < INT_MAX && dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    pq.push({dist[v], v});
                    from[v] = {u, i};
                }
            }
        }

        if (dist[sink] == INT_MAX)
            break;

        int bottleneck = INT_MAX;
        for (int v = sink; v != source; v = from[v].first) {
            int u = from[v].first;
            int edge_index = from[v].second;
            bottleneck = min(bottleneck, network[u][edge_index].capacity - network[u][edge_index].flow);
        }

        for (int v = sink; v != source; v = from[v].first) {
            int u = from[v].first;
            int edge_index = from[v].second;

            network[u][edge_index].flow += bottleneck;
            network[v][network[u][edge_index].residual].flow -= bottleneck;
            answer += bottleneck * network[u][edge_index].cost;
        }
    }

    return answer;
}

int main() {
    int n;
    fin >> n;

    network.resize(2 * n + 2);

    int source = 2 * n, sink = 2 * n + 1;
    for (int i = 0;i < n; ++i) {
        add_edge(source, i, 1, 0);
        add_edge(i + n, sink, 1, 0);
    }

    for (int i = 0;i < n;++i) {
        for (int j = 0;j < n;++j) {
            int cost; 
            fin >> cost; 
            add_edge(i, j + n, 1, cost);
        }
    }

    fout << min_cost_flow(source, sink);

    fin.close();
    fout.close();

    return 0;
}