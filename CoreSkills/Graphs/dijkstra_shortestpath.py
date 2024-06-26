import heapq

class Solution:
    def shortestPath(self, n: int, edges: list[list[int]], src: int) -> dict[int, int]:
        """
        - implement dijkstra's shortest path
        - input: weighted, directed graph and starting vertex
        - output: shortest distance from the start to every other vertex
        - if a vertex is unreachable from the source vertex, the shortest path distance is -1

        Input:
        n = 5 (number of vertices)
        edges = [[0,1,10], [0,2,3], [1,3,2], [2,1,4], [2,3,8], [2,4,2], [3,4,5]] (u, v, w) (edge from u to v with weight w)
        src = 0 (starting vertex)

        Output:
        {{0:0}, {1:7}, {2:3}, {3:9}, {4:5}} (key: vertex, value: shortest path)
        """
        # 1. Build adjacency list & output
        graph = {}
        shortestpaths = {}
        for i in range(n):
            graph[i] = [] # edges will be represented as [dst vertex, weight]
            shortestpaths[i] = -1
        # add edges to adjacency list
        for e in edges:
            u = e[0]
            v = e[1]
            w = e[2]
            graph[u].append([v,w])
        
        # 2. Setup Dijkstra's
        visited = set()
        visited.add(src) # mark src as visited
        minheap = []
        shortestpaths[src] = 0
        for edge in graph[src]:
            # add outgoing edges from the source to minheap
            heapq.heappush(minheap, (edge[1], edge[0])) # priority is determeined with respect to first element (cost)
            #(cost, dst)

        # 3. Execute Dijkstra's
        while len(minheap) > 0:
            edge = heapq.heappop(minheap) # min cost edge
            totalcost = edge[0]
            dst = edge[1]

            # update shortest path
            if dst not in visited:
                visited.add(dst)
                shortestpaths[dst] = totalcost
            
            # add adjacent edges
            for e in graph[dst]:
                v = e[0]
                w = e[1]
                if v not in visited: # if dst vertex unvisited (don't know shortest path)
                    heapq.heappush(minheap, (w + shortestpaths[dst], v))
        
        return shortestpaths

"""
Time Complexity? Basically we have E edges and for each edge we will push and pop from the minheap.
Pushing and popping takes logE because we could have E edges on the minheap so our time complexity is O(E*logE)
"""


            






        

    

