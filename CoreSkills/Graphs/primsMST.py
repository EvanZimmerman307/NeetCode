import heapq

class Solution:
    def minimumSpanningTree(self, n: int, edges: list[list[int]]) -> int:
        """
        - Implement prim's algorithm (minimum spanning tree)
        - What is a minimum spanning tree? An acyclic tree that connects all vertices in the graph for the 
        minimum cost (undirected graph)
        - Use V - 1 edges to connect V nodes
        - greedy algorithm: add the min edge to an unvisited node at each step (growing the tree)
        - find MST using Prim's and return total weight
        - return -1 if graph is unconnected

        Input:
        n = 5 (number of vertices)
        edges = [[0,1,10], [0,2,3], [1,3,2], [2,1,4], [2,3,8], [2,4,2], [3,4,5]] (u, v, w) (edge from u to v with cost w)

        Output:
        11
        """
        totalweight = 0
        
        # 1. Build adjacency list
        graph = {}
        for i in range(n):
            graph[i] = []
        
        # add edges to graph
        for e in edges:
            u = e[0]
            v = e[1] 
            w = e[2]
            # undirected - edge goes both ways, add edge to adjacency list of u and v
            graph[u].append([w, v]) # [weight, v]
            graph[v].append([w, u])
        
        # 2. setup Prim's
        visited = set()
        minheap = [] # contain tuples (weight, vertex)
        # start at 0
        visited.add(0)
        for e in graph[0]:
            weight = e[0]
            v = e[1]
            heapq.heappush(minheap, (weight, v))

        # 3. execute Prim's
        while len(minheap) > 0:
            e = heapq.heappop(minheap)
            weight = e[0]
            v = e[1]

            # updating the total weight
            if v not in visited:
                visited.add(v)
                totalweight += weight

            # add outgoing edges
            for edge in graph[v]:
                cost = edge[0]
                vertex = edge[1]
                if vertex not in visited:
                    heapq.heappush(minheap, (cost, vertex))
        
        # 4. return total weight or -1 if graph is unconnected
        if len(visited) != n:
            return -1
        
        return totalweight

"""
Time complexity: O(ElogE) because we have to process E edges by pushing and popping from the minheap which takes logE.
"""


        