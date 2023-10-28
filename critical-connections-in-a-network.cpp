// https://leetcode.com/problems/critical-connections-in-a-network/description/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    int timer = 0;
public:
    void dfs(int node,
        int parent,
        vector<vector<int>>& graph,
        vector<int>& t,
        vector<int>& l,
        vector<vector<int>>& bridges) {

        t[node] = l[node] = this->timer++;
        for (const auto& neighbor : graph[node]) {
            if (neighbor == parent) continue; 

            if (t[neighbor] != -1) {
                l[node] = min(l[node], l[neighbor]);
                continue; 
            }

            dfs(neighbor, node, graph, t, l, bridges);
            l[node] = min(l[node], l[neighbor]);

            if (l[neighbor] > t[node]) bridges.push_back({node, neighbor});
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        for (const auto& it : connections) {
            graph[it[0]].push_back(it[1]);
            graph[it[1]].push_back(it[0]);
        }

        vector<int> t(n, -1), l(n, -1);
        vector<vector<int>> bridges;

        dfs(0, -1, graph, t, l, bridges);
        return bridges;
    }
};
