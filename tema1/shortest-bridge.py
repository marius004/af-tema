# https://leetcode.com/problems/shortest-bridge

from collections import deque, defaultdict
from typing import List

class Solution:
    def __init__(self): 
        self.dirs = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        self.rows = 0
        self.cols = 0
    
    def find_island(self, grid: List[List[int]]):
        for row in range(self.rows):
            for col in range(self.cols): 
               if grid[row][col]: 
                   return (row, col)
        return (-1, -1)
        
    def shortestBridge(self, grid: List[List[int]]) -> int:
        self.rows, self.cols = len(grid), len(grid[0])
        island = self.find_island(grid)
       
        q, qi = deque([island]), deque([(island[0], island[1], 0)])
        seen = defaultdict(lambda: False, {})
       
        seen[island] = True
        while q: 
            x, y = q.popleft()
            for dir in self.dirs:
               new_x, new_y = x + dir[0], y + dir[1]
               if new_x in range(self.rows) and new_y in range(self.cols) and \
                   not seen[(new_x, new_y)] and grid[new_x][new_y] == 1:
                        q.append((new_x, new_y))
                        qi.append((new_x, new_y, 0))
                        seen[(new_x, new_y)] = True 
        
        while qi:
            x, y, cost = qi.popleft()
            for dir in self.dirs: 
                new_x, new_y = x + dir[0], y + dir[1]
                if not(new_x in range(self.rows) and new_y in range(self.cols)) or seen[(new_x, new_y)]:
                    continue 
                if grid[new_x][new_y] == 1:  
                    return cost
                
                qi.append((new_x, new_y, 1 + cost))
                seen[(new_x, new_y)] = True
        
        return -1
    
grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
solver = Solution()

print(solver.shortestBridge(grid))