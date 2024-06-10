"""
Design a directed Graph class.

Your Graph class should support the following operations:

Graph() will initialize an empty directed graph.
void addEdge(int src, int dst) will add an edge from src to dst if it does not already exist. If either src or dst do not exist, add them to the graph.
bool removeEdge(int src, int dst) will remove the edge from src to dst if it exists. Return whether the edge was removed. Either src or dst may not exist in the graph.
bool hasPath(int src, int dst) will return whether there is a path from src to dst. Assume both src and dst exist in the graph.
Constraints:

Each vertex value will be a unique integer.
Multiple edges from one vertex to another are not allowed.
A vertex will not have an edge to itself, but the graph may contain a cycle.
The graph is not necessarily connected (there may be disconnected components).
"""

from collections import deque

class Graph:
    
    def __init__(self):
        self.adjacency_list = {} # {vertex: neighbors set}
        # We will use a set for faster lookup if an edge exists

    def addEdge(self, src: int, dst: int) -> None: # add an edge from src to dst O(1)
        if src not in self.adjacency_list:
            self.adjacency_list[src] = set()
        if dst not in self.adjacency_list:
            self.adjacency_list[dst] = set()
        
        if dst not in self.adjacency_list[src]: # add edge if it does not exist
            self.adjacency_list[src].add(dst)
            print("Adding edge:", src, "->", dst)
            print(self.adjacency_list)
        return

    def removeEdge(self, src: int, dst: int) -> bool: # will remove the edge from src to dst if it exists O(1)
        # Either src or dst may not exist in the graph.
        if src in self.adjacency_list:
            if dst in self.adjacency_list[src]:
                self.adjacency_list[src].remove(dst)
                print("Removing edge:", src, "->", dst)
                print(self.adjacency_list)
                return True
        return False

    def hasPath(self, src: int, dst: int) -> bool: # return if there is a path from src to dst O(V + E)
        #BFS approach

        visited = set()
        queue = deque()
        visited.add(src)
        queue.append(src)

        while queue:
            current = queue.popleft() # popping from the head
            for vertex in self.adjacency_list[current]:
                if vertex == dst: # checking if dst is an adjacent vertex
                    return True
                if vertex not in visited: # adding unvisited nodes to the BFS search
                    queue.append(vertex)
                    visited.add(vertex)
        return False


"""
Input:
["addEdge", 1, 2, "addEdge", 2, 3, "hasPath", 1, 3, "hasPath", 3, 1, "removeEdge", 1, 2, "hasPath", 1, 3]

Output:
[null, null, true, false, true, false]

Input:
["addEdge", 1, 2, "addEdge", 2, 3, "addEdge", 3, 1, "hasPath", 1, 3, "hasPath", 3, 1]

Output:
[null, null, null, true, true]
"""