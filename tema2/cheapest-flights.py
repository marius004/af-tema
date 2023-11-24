# https://leetcode.com/problems/cheapest-flights-within-k-stops/description/

from typing import List
import heapq

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        graph = [[] for _ in range(n)]
        for u, v, w in flights:
            graph[u].append((v, w))
            
        hp, visited = [(0,0, src)], {}
        while hp: 
            cost, stops, city = heapq.heappop(hp)
            visited[city] = stops
            
            if city == dst: 
                return cost
            
            if stops > k: 
                continue
            
            for nextCity, nextCityCost in graph[city]: 
                if nextCity not in visited or visited[nextCity] > stops: 
                    heapq.heappush(hp, (cost + nextCityCost, stops + 1, nextCity))
        
        return -1