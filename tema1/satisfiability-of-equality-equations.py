# https://leetcode.com/problems/satisfiability-of-equality-equations/

from typing import List

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
        
    def equationsPossible(self, equations: List[str]) -> bool:
        self.parent = [-1 for _ in range(26)]
        
        for equation in equations: 
            if equation[1] == "=":
                x, y = ord(equation[0]) - ord('a'), ord(equation[3]) - ord('a')
                self.union(x, y)
        
        for equation in equations: 
            x, y = ord(equation[0]) - ord('a'), ord(equation[3]) - ord('a')
            if equation[1] == "!" and self.find(x) == self.find(y): 
                    return False
                 
        return True