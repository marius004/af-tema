# https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/

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

    def distanceLimitedPathsExist(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[bool]:
        queries = sorted((w, u, v, i) for i, (u, v, w) in enumerate(queries))
        edges = sorted((w, u, v) for u, v, w in edges)
        
        self.parent, answer = [-1] * n, [False] * len(queries)
        
        idx = 0
        for w, u, v, i in queries: 
            while idx < len(edges) and edges[idx][0] < w: 
                self.union(edges[idx][1], edges[idx][2])
                idx += 1
            answer[i] = self.find(u) == self.find(v)
        
        return answer

solution = Solution()
print(solution.distanceLimitedPathsExist(3, [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], [[0,1,2],[0,2,5]]))
