// https://www.infoarena.ro/problema/rusuoaica

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("rusuoaica.in");
ofstream g("rusuoaica.out");

struct Edge {
    int x, y, cost;
};

int N, M, A;
vector < Edge > edges;
vector < int > disjoint;

void collapse(int node, const int& root) {

    while(node != root) {
        int aux = disjoint[node];

        disjoint[node] = root;
        node = aux;
    }
}

int Find(const int& node) {

    int root = node;

    while(disjoint[root] > 0)
        root = disjoint[root];

    collapse(node, root);

    return root;
}

void Union(int rootX, int rootY) {

    if(-disjoint[rootX] < -disjoint[rootY])
        swap(rootX, rootY);

    disjoint[rootX] += disjoint[rootY];
    disjoint[rootY] = rootX;
}

int main() {

    f >> N >> M >> A;

    edges.resize(M);
    for(Edge& e : edges)
        f >> e.x >> e.y >> e.cost;

    disjoint.resize(N + 1, -1);

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b ){
        return a.cost < b.cost;
    });

    int sol = 0;
    for(Edge& e : edges) {

        const int rootX = Find(e.x);
        const int rootY = Find(e.y);

        if(rootX != rootY) {

            // daca vand si cumpar
            if(e.cost > A) {
                sol -= e.cost; // vand pe cel cu costul mai mare
                sol += A; // cumpar pe cel cu costul mai mic
            }else {
                sol += e.cost;
            }

            Union(rootX, rootY);
        }else {

            sol -= e.cost;

        }
    }

    // nr de paduri disjunte == nr de componente conexe
    int conex = 0;
    for(int i = 1;i <= N;++i)
        if(disjoint[i] < 0)
            conex++;

    g << sol + (conex - 1) * A;

    return 0;
}