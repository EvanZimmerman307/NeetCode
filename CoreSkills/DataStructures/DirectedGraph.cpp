/*
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
*/
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Graph {    
public:
    std::unordered_map<int, std::unordered_set<int>> adjacency_list;
    // Key: vertex, Val: set of adjacent vertices

    Graph() {}

    void addEdge(int src, int dst) { // add edge from src to dst
        // If either src or dst do not exist, add them to the graph.

        if (adjacency_list.find(src) == adjacency_list.end()){
            adjacency_list[src];
        }
        if (adjacency_list.find(dst) == adjacency_list.end()){
            adjacency_list[dst];
        }

        // Add the edge if it does not exist
        if (adjacency_list[src].find(dst) == adjacency_list[src].end()) {
            adjacency_list[src].insert(dst);
        }
        return;
    }

    bool removeEdge(int src, int dst) { // remove the edge from src to dst if it exists.
        //  Either src or dst may not exist in the graph.
        if (adjacency_list.find(src) !=  adjacency_list.end()) {
            if (adjacency_list[src].find(dst) != adjacency_list[src].end()) {
                adjacency_list[src].erase(dst);
                return true;
            }
        }
        return false;
    }

    bool hasPath(int src, int dst) { // return whether there is a path from src to dst.
        // BFS approach
        std::unordered_set<int> visited;
        std::queue<int> q;
        visited.insert(src);
        q.push(src);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (auto it = adjacency_list[current].begin(); it != adjacency_list[current].end(); ++it) {
                if (*it == dst) { // dst is in adjacency list
                    return true;
                }
                if (visited.find(*it) == visited.end()) { // haven't seen this node yet
                    visited.insert(*it);
                    q.push(*it);
                }
            }
        }
        return false;
    }
};

/*
Input:
["addEdge", 1, 2, "addEdge", 2, 3, "hasPath", 1, 3, "hasPath", 3, 1, "removeEdge", 1, 2, "hasPath", 1, 3]

Output:
[null, null, true, false, true, false]

Input:
["addEdge", 1, 2, "addEdge", 2, 3, "addEdge", 3, 1, "hasPath", 1, 3, "hasPath", 3, 1]

Output:
[null, null, null, true, true]
*/