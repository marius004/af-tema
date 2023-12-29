// https://infoarena.ro/job_detail/2663563?action=view-source

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

ifstream f("negot.in");
ofstream g("negot.out");

const int NMAX = 41005;

struct Edge {

    int to, capacity, flow, opposite;

    Edge(const int& to, const int& capacity, const int& flow) {
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
        this->opposite = -1;
    }
};

int N, M, K, SOURCE, DESTINATION;
pair < int, int > parent[NMAX];
vector < Edge > G[NMAX];
bitset < NMAX > vis;

void link(const int& u, const int& v, const int& capacity) {

    G[u].push_back( { v, capacity, 0 } );
    G[v].push_back( { u, 0, 0 } );

    G[u].back().opposite = (int)G[v].size() - 1;
    G[v].back().opposite = (int)G[u].size() - 1;
}

bool bfs() {

    vis.reset();
    queue < int > q;

    q.push(SOURCE);
    vis[SOURCE] = 1;
    parent[SOURCE] = { 0, 0 };

    while(!q.empty()) {

        const int node = q.front();
        q.pop();

        for(auto& neighbor : G[node]) {

            if(!vis[neighbor.to] && neighbor.capacity > neighbor.flow) {
                vis[neighbor.to] = true;
                q.push(neighbor.to);
                parent[neighbor.to] = { node, neighbor.opposite };

                if(neighbor.to == DESTINATION)
                    return true;
            }
        }
    }

    return false;
}

int main() {

    f >> N >> M >> K;

    SOURCE = 0;
    DESTINATION = N + M + 1;

    for(int i = 1;i <= N;++i) {

        link(SOURCE, i, K);

        int len; f >> len;
        while(len--) {
            int x; f >> x;
            link(i, N + x, 1);
        }
    }

    for(int i = N + 1; i < DESTINATION;++i)
        link(i, DESTINATION, 1);

    int flow{};
    while(bfs()) {

        for(auto& node : G[DESTINATION]) {

            int aux{};
            for(auto& it : G[node.to])
                if(it.to == DESTINATION)
                    break;
                else aux++;

            if(vis[node.to] && G[node.to][aux].capacity > G[node.to][aux].flow) {

                int minnEdge = G[node.to][aux].capacity - G[node.to][aux].flow;
                int u = node.to;

                vector < pair < pair < int, int >, pair < int, int > > > paths;
                paths.push_back({ make_pair(node.to, aux), make_pair(DESTINATION, parent[DESTINATION].second) });

                while(u != 0) {

                    int ind{};
                    for(auto& e : G[ parent[u].first ]) {
                        if (e.to == u) {
                            minnEdge = min(minnEdge, G[ parent[u].first ][ind].capacity -  G[ parent[u].first ][ind].flow);
                            paths.push_back( { make_pair(parent[u].first, ind), make_pair(u, parent[u].second) });
                            break;
                        }
                        ind++;
                    }

                    u = parent[u].first;
                }

                flow += minnEdge;
                for(auto it : paths) {
                    G[ it.first.first  ][it.first.second].flow += minnEdge;
                    G[ it.second.first ][it.second.second].flow -= minnEdge;
                }
            }

        }
    }

    g << flow;

    return 0;
}