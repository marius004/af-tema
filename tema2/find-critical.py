# https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/

from typing import List
from decimal import Decimal

class Solution:
    def __init__(self) -> None:
        self.parent = []
       
    def find(self, node: int): 
        if self.parent[node] < 0: 
            return node 

        self.parent[node] = self.find(self.parent[node])
        return self.parent[node]
    
    def union(self, x: int, y: int): 
        rootX, rootY = self.find(x), self.find(y)
        if -self.parent[rootX] < -self.parent[rootY]: 
            rootX, rootY = rootY, rootX 
        
        if rootX == rootY: 
           return 
        
        self.parent[rootX] += self.parent[rootY]
        self.parent[rootY] = rootX
    
    def findMST(self, n: int, edges: List[List[int]], blockage: int, existing: int):
        self.parent, weight = [-1] * n, 0
        
        if existing != -1: 
            weight += edges[existing][2]
            self.union(edges[existing][0], edges[existing][1])
        
        for i, edge in enumerate(edges): 
            if i == blockage or self.find(edge[0]) == self.find(edge[1]):
                continue
            self.union(edge[0], edge[1])
            weight += edge[2]
        
        return weight if all([self.find(0) == self.find(i) for i in range(1, n)]) else Decimal('Infinity')
    
    def findCriticalAndPseudoCriticalEdges(self, n: int, edges: List[List[int]]) -> List[List[int]]:            
        answer, self.parent, edges = [[], []], [-1] * n, \
            sorted([edge + [index] for index, edge in enumerate(edges)], key=lambda value: value[2]) 
        
        weight = self.findMST(n, edges, -1, -1)
        for i, edge in enumerate(edges): 
            if weight < self.findMST(n, edges, i, -1): 
                answer[0].append(edge[3])
            elif weight == self.findMST(n, edges, -1, i): 
                answer[1].append(edge[3])
        
        return answer 
