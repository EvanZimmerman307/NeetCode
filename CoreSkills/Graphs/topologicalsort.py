class Solution:
    def topologicalSort(self, n: int, edges: list[list[int]]) -> list[int]:
        """
        - implement topological sort
        - order the vertices of a directed, acyclic graph such that for every edge (u,v), 
        u comes before v in the ordering
        - return the order as a list of vertex labels - any valid ordering works
        - if a graph contains a cycle, return an empty list (topological sort is not possible for graphs with cycles)
        - n: number of vertices, labeled 0 to n - 1
        - edges: list of pairs (u,v) where edge is from u to v
        - topological sort can be run starting from any node
        - topological sort follows a dfs, post-order traversal approach

        Input:
        n = 6
        edges = [[2,3], [3,1], [4,0], [4,1], [5,0], [5,2]]

        Output:
        [5, 4, 2, 3, 1, 0]
        """

        # build the graph
        vertices = range(n) # make a list of vertices
        graph = {}
        for i in range(n):
            graph[i] = []
        for e in edges:
            u = e[0]
            v = e[1]
            graph[u].append(v)
        
        # setup topological sort
        visited = set()
        topsort = []
        path = set() # this could be a stack

        # execute dfs on each vertex
        for vertex in vertices:
            possible = self.dfs(vertex, graph, visited, topsort, path)
            if not possible:
                return []

        topsort.reverse()
        return topsort

    def dfs(self, vertex, graph, visited, topsort, path):
        if vertex in visited: # stop dfs if already visited vertex
            return True
        if vertex in path: # cycle detected
            print("cycle detected")
            return False
        
        path.add(vertex)
        for u in graph[vertex]: # loop through adjacency list
            possible = self.dfs(u, graph, visited, topsort, path)
            if not possible: # cycle detected
                return False
        visited.add(vertex) 
        path.remove(vertex) # remove from path - make this vertex accesible for dfs from another vertex
        topsort.append(vertex) # append after dfs on all adjacent vertices
        return True

    # Time Complexity O(V+E) because we have to add and remove from the path which could be V vertices. 
    # We have to process V vertices which could take E edges to reach.


            
        



        
        