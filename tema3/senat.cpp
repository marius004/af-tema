// https://www.infoarena.ro/job_detail/2666359?action=view-source 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

ifstream f("senat.in");
ofstream g("senat.out");

const int NMAX = 101;

int N, M, L[NMAX], R[NMAX];
vector < int > G[NMAX];
bitset < NMAX > U;

vector < int > parse(const std::string& str) {

    vector < int > sol;
    int nr{}, i{};

    while(i < str.length()) {
        if(str[i] >= '0' && str[i] <= '9')
            nr = nr * 10 + (str[i] - '0');
        else if(nr ) {
            sol.emplace_back(nr);
            nr = 0;
        }

        i++;
    }

    if(nr != 0)
        sol.emplace_back(nr);

    return sol;
}

bool cupleaza(const int& node) {

    if(U[node] == 1)
        return 0;

    U[node] = 1;

    for(const auto& neighbor : G[node]) {
        if(R[neighbor] == 0) {
            R[neighbor] = node;
            L[node] = neighbor;
            return true;
        }
    }

    for(const auto& neighbor : G[node]) {
        if(cupleaza(R[neighbor])) {
            R[neighbor] = node;
            L[node] = neighbor;
            return true;
        }
    }

    return false;
}

int main() {

    f >> N >> M;

    f.get();

    for(int i = 1;i <= M;++i) {
        string s;
        getline(f, s);

        vector < int > couple = parse(s);

        for(const auto& it : couple)
            G[i].push_back(it);
    }

    bool ok{ true };
    do {

        U.reset();
        ok = false;

        for(int i = 1;i <= M;++i)
            if(L[i] == 0)
                ok |= cupleaza(i);

    } while(ok);

    bool sol{ true };
    for(int i = 1;i <= M;++i)
        if(!L[i])
            sol = false;


   if(!sol)
       g << 0;
   else
       for(int i = 1;i <= M;++i)
           g << L[i] << '\n';

    return 0;
}