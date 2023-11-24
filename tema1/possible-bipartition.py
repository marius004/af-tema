# https://leetcode.com/problems/possible-bipartition/

from collections import deque
from typing import List

class Solution:
    def possibleBipartition(self, n: int, dislikes: List[List[int]]) -> bool:
        if len(dislikes) == 0: 
            return True 
        
        graph = [[] for _ in range(n)]
        for dislike in dislikes: 
            graph[dislike[0] - 1].append(dislike[1] - 1) 
            graph[dislike[1] - 1].append(dislike[0] - 1)
        
        colors  = [-1] * n
        for node in range(n): 
            if colors[node] == -1: 
                if not self.isBipartite(graph, node, colors):
                    return False
                
        return True
                
    def isBipartite(self, graph: List[List[int]], node: int, colors: List[int]): 
        colors[node] = 1
        queue = deque([node])
        
        while len(queue) > 0: 
            curr = queue.popleft()
            
            for neighbor in graph[curr]: 
                if colors[neighbor] == -1: 
                   colors[neighbor] = 1 - colors[curr]
                   queue.append(neighbor)
                elif colors[neighbor] == colors[curr]: 
                    return False
                
        return True

solver = Solution()
print(solver.possibleBipartition(4, [[1,2], [1, 3], [2, 4]]))
print(solver.possibleBipartition(3, [[1,2], [1, 3], [2, 3]]))