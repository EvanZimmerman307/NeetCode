import heapq

class Solution:
    def minimumSpanningTree(self, n: int, edges: list[list[int]]) -> int:
        """
        - implement kruskal's MST algo
        - minimum spanning tree (MST) is the set of edges that connects all the vertices in an undirected graph for the lowest total cost
        - MSTs can not have cycles
        - kruskal's algo: use the unionfind data structure to manage connecting the graph, put all the edges on a min heap
        - pop off the min edge, union the vertices if possible, unionfind ensures we don't union vertices already connected
        - return the total weight or -1 if unconnected graph.
        - n: number of vertices, vertices are labeled 0 to n-1
        - edges: list of tuples (u,v,w) where u and v are vertices and w is the weight
        """
        # setup kruskal's
        totalweight = 0
        mst_edges = 0 
        unionfind = UnionFind(n)
        minheap = []
        for e in edges:
            u = e[0]
            v = e[1]
            w = e[2]
            heapq.heappush(minheap, (w, u, v))
        
        # execute kruskal's
        while len(minheap) > 0:
            edge = heapq.heappop(minheap)
            w = edge[0]
            u = edge[1]
            v = edge[2]
            connect = unionfind.union(u,v) # connect is false if u and v are already connected
            if connect: # successfully unioned vertices
                totalweight += w
                # increment edge counter
                mst_edges += 1
                if mst_edges == n-1: # MST is built when we have n-1 edges
                    return totalweight
        
        return -1

        # runtime is O(ElogE) because we have to push and pop E edges from the minheap
        # pushing and popping takes logE time
        # the the time complexity of the minheap is worse than union find 

class UnionFind:
    
    def __init__(self, n: int): # initialize a disjoint set of size n.
        self.parents = {}
        self.rank = {}
        for i in range(n):
            self.parents[i] = i
            self.rank[i] = 0

    def find(self, x: int) -> int: # will return the root of the component that x belongs to.
        node = x
        while (self.parents[node] != node):
            self.parents[node] = self.parents[self.parents[node]] # path compression
            node = self.parents[node]
        return node
        
    def isSameComponent(self, x: int, y: int) -> bool: # will return whether x and y belong to the same component.
        return self.find(x) == self.find(y) # share the same root

    def union(self, x: int, y: int) -> bool:
        rootX, rootY = self.find(x), self.find(y)
        if rootX == rootY:
            return False
        else:
            # Union by rank
            if self.rank[rootX] > self.rank[rootY]:
                self.parents[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parents[rootX] = rootY
            else:
                self.parents[rootX] = rootY
                self.rank[rootY] += 1
            return True

    def getNumComponents(self) -> int: # O(n * 1), call find on every single node
        components = set()
        # find the root of each node
        for i in range(len(self.parents)):
            root = self.find(i)
            components.add(root)
        return len(components) # num unique roots


