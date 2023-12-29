#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:

    int solve(int source, vector<vector<int>>& cache, const vector<vector<int>>& dist, int mask = 0) {
        if (cache[source][mask] != -1)
            return cache[source][mask];

        bool allVisited = true;
        int minDistance = INT_MAX; 

        for (int neighbor = 0; neighbor < dist.size(); ++neighbor) {
            if (mask & (1 << neighbor)) continue;
            allVisited = false;
            int extra = solve(neighbor, cache, dist, mask | (1 << neighbor));
            minDistance = min(minDistance, dist[source][neighbor] + extra);
        }

        return cache[source][mask] = (allVisited ? 0 : minDistance);
    }

    int shortestPathLength(vector<vector<int>>& graph) {
        vector<vector<int>> dist(graph.size(), vector<int>(graph.size(), INT_MAX));
        for (int node = 0; node < graph.size(); ++node) {
            dist[node][node] = 0;
            for (int& neighbor : graph[node]) 
                dist[node][neighbor] = 1;
        }

        for (int k = 0; k < graph.size(); ++k)
            for (int i = 0; i < graph.size(); ++i)
                for (int j = 0; j < graph.size(); ++j)
                    if (dist[i][k] < INT_MAX && 
                            dist[k][j] < INT_MAX &&
                            dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

        vector<vector<int>> dp(graph.size(), vector<int>(1 << (graph.size() + 1) + 1, -1));

        int result = INT_MAX;
        for (int node = 0; node < graph.size(); ++node)
            result = min(result, solve(node, dp, dist));

        return result;
    }
};
