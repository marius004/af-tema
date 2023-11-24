// https://www.infoarena.ro/problema/cablaj

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <iomanip>

using namespace std;

ifstream f("cablaj.in");
ofstream g("cablaj.out");

struct Point {
    int x, y;

    Point() {
        x = y = 0;
    }

    Point(const int& x, const int& y) {
        this->x = x;
        this->y = y;
    }

    double calculateDistance(const Point& p) {
        return sqrt( (this->x - p.x) * (this-> x - p.x) + (this->y - p.y) * (this->y - p.y));
    }
};

const int NMAX = 3'001;
const int INF = (1 << 30);

int N;
double d[NMAX];
bool vis[NMAX];
vector < Point > points;

int selectMin() {

    double minn{ INF };
    int minnIndex{};

    for(int i = 0;i < N;++i) {
        if (d[i] < minn && !vis[i]) {
            minn = d[i];
            minnIndex = i;
        }
    }

    return minnIndex;
}

int main() {

    f >> N;

    points.resize(N);
    for(int i = 0;i < N;++i)
        f >> points[i].x >> points[i].y;

    for(int i = 0;i < N;++i)
        d[i] = DBL_MAX;

    d[0] = 0;
    for(int i = 0;i < N - 1;++i) {

        int u = selectMin();

        vis[u] = true;

        for(int v = 0; v < N;++v) {
            if(u == v) continue;

            double dist = points[u].calculateDistance(points[v]);

            if(!vis[v] && dist < d[v])
                d[v] = dist;
        }
    }

    double sol = 0;
    for(int i = 0;i < N;++i)
        sol += d[i];

    g << fixed << setprecision(12) << sol;

    return 0;
}