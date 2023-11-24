// https://www.infoarena.ro/problema/apm2

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

ifstream f("apm2.in");
ofstream g("apm2.out");

struct Edge {
    int x, y, cost;

    friend istream& operator >> (istream& stream, Edge& e) {
        stream >> e.x >> e.y >> e.cost;
        return stream;
    }

    friend ostream& operator << (ostream& stream, Edge& e) {
        stream << e.x << ' ' << e.y << ' ' << e.cost;
        return stream;
    }
};

const int NMAX = 100'001;

int N, M, K, depth[NMAX];
vector < pair < int, int > > G[NMAX];
vector < int > DOWN[NMAX];
vector < pair < int, int > > UP[NMAX];
bool vis[NMAX];

struct Pq_Comparator {

    bool operator()(Edge& a, Edge& b) {
        return a.cost > b.cost;
    }
};

void dfs(int node, int parent) {
    depth[node] = 1 + depth[parent];

    for(int x : DOWN[node])
        dfs(x, node);
}

pair < int, int > urca(int node) {

    for(pair < int, int > x : UP[node])
        if(depth[x.first] < depth[node])
            return x;

    return { -1, -1 };
}

int main() {

    f >> N >> M >> K;

    for(int i = 0;i < M;++i) {
        Edge e;
        f >> e;

        if(e.x > e.y)
            swap(e.x, e.y);

        G[e.x].push_back( { e.y, e.cost } );
        G[e.y].push_back( { e.x, e.cost } );
    }

    priority_queue < Edge, vector < Edge >, Pq_Comparator > pq;

    for(pair < int, int > x : G[1])
        pq.push({1, x.first, x.second } );

    int cnt = 0, cost = 0;
    while(!pq.empty()) {

        auto tp = pq.top();
        pq.pop();

        if(!vis[tp.y]) {

            DOWN[tp.x].push_back(tp.y);
            UP[tp.y].push_back( { tp.x, tp.cost } );

            vis[tp.x] = vis[tp.y] = true;
            cost += tp.cost;

            for(pair < int, int > x : G[tp.x])
                pq.push({ tp.x, x.first, x.second });

            for(pair < int, int > x : G[tp.y])
                pq.push({ tp.y, x.first, x.second });

            cnt++;

            if(cnt == N - 1)
                break;
        }
    }

    int root{};
    for(int i = 1;i <= N;++i)
        if(UP[i].size() == 0)
            root = i;

    dfs(root, 0);

    while(K--) {

        int x, y, maxx{};
        f >> x >> y;

        while(depth[x] > depth[y]) {
            pair < int, int > susX = urca(x);
            maxx = max(maxx, susX.second);
            x = susX.first;
        }

        while(depth[y] > depth[x]) {
            pair < int, int > susY = urca(y);
            maxx = max(maxx, susY.second);
            y = susY.first;
        }

        while(x != y) {
            pair < int, int > susX = urca(x);
            maxx = max(maxx, susX.second);
            x = susX.first;

            pair < int, int > susY = urca(y);
            maxx = max(maxx, susY.second);
            y = susY.first;
        }

        g << maxx - 1 << '\n';
    }

    return 0;
}