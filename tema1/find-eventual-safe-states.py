# https://leetcode.com/problems/find-eventual-safe-states

from typing import List
from collections import deque

class Solution:
    def eventualSafeNodes(self, input: List[List[int]]) -> List[int]:
        graph  = [[] for _ in range(len(input))]
        degree = [0] * len(input) 
        
        for node in range(len(input)):
            for neighbor in input[node]:
                graph[neighbor].append(node)
                degree[node] += 1

        safe, q = [], deque([])
        for node in range(len(input)): 
            if degree[node] == 0: 
               safe.append(node)
               q.append(node)
        
        while q:
            node = q.popleft()
            for neighbor in graph[node]: 
                degree[neighbor] -= 1
                if degree[neighbor] == 0: 
                    safe.append(neighbor)
                    q.append(neighbor)
        
        return sorted(safe)

graph = [[1,2],[2,3],[5],[0],[5],[],[]]
solver = Solution()

print(solver.eventualSafeNodes(graph))