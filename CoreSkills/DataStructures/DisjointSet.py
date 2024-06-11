"""
Design a Disjoint Set (aka Union-Find) class.

Your UnionFind class should support the following operations:

UnionFind(int n) will initialize a disjoint set of size n.
int find(int x) will return the root of the component that x belongs to.
bool isSameComponent(int x, int y) will return whether x and y belong to the same component.
bool union(int x, int y) will union the components that x and y belong to. If they are already in the same component, return false, otherwise return true.
int getNumComponents() will return the number of components in the disjoint set.
"""

"""
With proper path compression and union by rank/size, 
every operation should be O(1) in the average case.
"""


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


"""
Input:
["UnionFind", 10, "isSameComponent", 1, 3, "union", 1, 2, "union", 2, 3, "getNumComponents", "isSameComponent", 1, 3]

Output:
[null, 1, false, true, true, 8, true]
"""