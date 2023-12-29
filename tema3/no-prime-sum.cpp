#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX_PRIME = 2e5 + 1;
const int MAX_SIZE  = 2e3 + 1;

bool isPrime[MAX_PRIME], isMatched[MAX_SIZE];
vector<int> leftNodes, rightNodes;
vector<vector<int>> graph;
int match[MAX_SIZE];
bitset<MAX_SIZE> U;

void sieve() {
    isPrime[0] = isPrime[1] = true;
    for(int i = 4;i < MAX_PRIME; i += 2)
        isPrime[i] = true;
    
    for(int i = 3;i < MAX_PRIME; i += 2) {
        if(!isPrime[i]) {
            for(int j = i + i;j <= MAX_PRIME;j += i)
                isPrime[j] = true;
        }
    }
}

bool cupleaza(int node) {
    if (U[node] == 1)
        return false; 

    U[node] = 1;

    for (int neighbor : graph[node]) {
        if (!isMatched[neighbor]) {
            isMatched[node] = isMatched[neighbor] = true;

            match[node] = neighbor;
            match[neighbor] = node; 
            
            return true;
        }
    }

    for (int neighbor : graph[node]) {
        if (cupleaza(match[neighbor])) {
            isMatched[node] = isMatched[neighbor] = true;

            match[node] = neighbor;
            match[neighbor] = node;

            return true;
        }
    }

    return false;
}

int main() {
    sieve();

    int n; 
    cin >> n;

    for (int i = 0;i < n; ++i) {
        int value; 
        cin >> value; 

        if (value & 1)
            leftNodes.push_back(value);
        else 
            rightNodes.push_back(value);
    }

    graph.resize((int) leftNodes.size());
    for (int i = 0;i < (int) leftNodes.size(); ++i) {
        for (int j = 0;j < (int) rightNodes.size(); ++j) {
            if (isPrime[leftNodes[i] + rightNodes[j]]) continue;
            graph[i].push_back(j + leftNodes.size());
        }
    }

    bool ok;
    do {
        ok = false; 
        U.reset();

        for (int i = 0;i < (int) leftNodes.size(); ++i) {
            if (match[i] == 0)
                ok |= cupleaza(i);
        }
    } while (ok);

    vector<int> unselected;
    vector<bool> selected(n, false);

    for (int i = 0;i < (int) leftNodes.size(); ++i) {
        if (isMatched[i])
            selected[i] = true;
        else
            unselected.push_back(i);
    }

    while (!unselected.empty()) {
        int node = unselected.back();
        unselected.pop_back();

        for (auto neighbor : graph[node]) {
            if (!selected[neighbor]) {
                int neighbor_pair = match[neighbor];
                if (selected[neighbor_pair]) {
                    unselected.push_back(neighbor_pair);
                    selected[neighbor_pair] = false;
                }
                selected[neighbor] = true;
            }
        }
    }

    int counter = 0;
    for (auto it : selected)
        counter += it;

    cout << counter << '\n';
    for (int i = 0;i < n; ++i) {
        if (!selected[i]) continue; 

        if (i < (int) leftNodes.size()) 
            cout << leftNodes[i] << ' ';
        else 
            cout << rightNodes[i - (int)leftNodes.size()] << ' ';
    }
    
    return 0;
}