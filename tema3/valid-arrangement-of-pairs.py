# https://leetcode.com/problems/valid-arrangement-of-pairs/submissions/
from typing import List

class Solution:
    def findStart(self, graph: dict):
        in_deg, out_deg = {}, {}
        
        for node in graph.keys(): 
            for neighbor in graph[node]: 
                in_deg[neighbor] = 1 + in_deg.get(neighbor, 0) 
                out_deg[node] = 1 + out_deg.get(node, 0)
        
        start = -1
        for node in  graph.keys(): 
            if out_deg.get(node, 0) - in_deg.get(node, 0) == 1: 
                return node
            
            if out_deg[node] > 0 and start == -1: 
                start = node 
        
        return start
            
    
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = {}
        for pair in pairs: 
            if graph.get(pair[0], None) is None: 
                graph[pair[0]] = []
            graph[pair[0]].append(pair[1])

        answer = []
        def dfs(node: int): 
            while graph.get(node, []): 
                dfs(graph[node].pop(0))
            answer.append(node)
            
        dfs(self.findStart(graph))
        path = list(reversed(answer))
        
        solution = []
        for i in range(1, len(path)):
            solution.append([path[i - 1], path[i]])
            
        return solution