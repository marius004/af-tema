# https://leetcode.com/problems/reconstruct-itinerary/submissions/
from collections import defaultdict
from typing import List

class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        graph = {}
        for ticket in tickets: 
            if graph.get(ticket[0], None) is None: 
                graph[ticket[0]] = []
            graph[ticket[0]].append(ticket[1])

        for values in graph.values(): 
            values.sort()    
        
        answer = []
        def dfs(node: str): 
            while graph.get(node, []): 
                dfs(graph[node].pop(0))
            answer.append(node)
            
        dfs("JFK")
        return reversed(answer)