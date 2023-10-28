// https://leetcode.com/problems/course-schedule-ii/
#include <vector>

using namespace std;

enum Status {
  NotVisited,
  Visited,
  Scheduled,
};

class Solution {
public:
  vector<vector<int>> buildGraph(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);

    for (const auto& it : prerequisites)
      graph[it[0]].push_back(it[1]);

    return graph;
  }

  bool dfs(int node, vector<vector<int>>& graph, vector < int >& order, vector<Status>& status) {
    if (status[node] == Scheduled)
      return false;

    status[node] = Visited;
    for (const auto& neighbor : graph[node]) {
      if (status[neighbor] == Visited)
        return true; 
      if (dfs(neighbor, graph, order, status))
        return true;
    }

    order.push_back(node);
    status[node] = Scheduled;

    return false;
  }

  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) { 
    auto graph = buildGraph(numCourses, prerequisites);

    vector <Status> status (numCourses, NotVisited);
    vector < int > order;
   
    for (int i = 0;i < numCourses; ++i) {
      if (status[i] != Scheduled && dfs(i, graph, order, status))
        return {}; 
    }
    
    return order;
  }
};
