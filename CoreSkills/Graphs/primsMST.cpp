#include <unordered_map>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <queue>

class Solution {
public:
    int minimumSpanningTree(std::vector<std::vector<int>>& edges, int n) {
        /*
        - implement Prim's MST algo
        - An MST is the tree (set of edges) that connects all vertices in an undirected graph for the minimum possible cost
        - An MST is acylic
        - Algo: starting from an arbitrary vertex, add to the MST the smallest cost edge to an unvisited node
        - Similar to Dijkstra's and bfs: use a minheap to keep track of edges and a set to keep track of visited nodes
        - add outgoing edges to the minheap, process the cheapest edge to an unvisited node
        - input: weighted undirected graph
        - edges: a vector of vectors (u,v,w) where u and v are vertices and w is weight
        - n: number of vertices
        - Output: total weight of the MST (if the graph is not connected return -1)

        Input:
        n = 5
        edges = [[0,1,10], [0,2,3], [1,3,2], [2,1,4], [2,3,8], [2,4,2], [3,4,5]]

        Output:
        11
        */

        // build adjacency list
        std::unordered_map<int, std::vector<std::tuple<int,int>>> graph; // key: vertex, value: vector of tuples(weight, dst vertex)
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            // add the edge to the adjacency list of u and v
            graph[u].push_back(std::make_tuple(w, v));
            graph[v].push_back(std::make_tuple(w, u));
        }

        // setup prim's (start at vertex 0)
        std::unordered_set<int> visited;
        std::priority_queue<std::tuple<int,int>> minheap; // maxheap by default, push edges with negative weight to achieve a minheap
        int totalweight = 0;
        visited.insert(0);
        for (std::tuple<int,int> edge: graph[0]) {
            int w = get<0>(edge);
            int dst = get<1>(edge);
            minheap.push(std::make_tuple(-1 * w, dst));
        }

        // execute prim's
        while (!minheap.empty()) {
            auto edge = minheap.top();
            minheap.pop();
            int w = get<0>(edge) * -1; // make the weight a positive number
            int dst = get<1>(edge);

            // add edge to MST if dst is unvisited
            if (visited.find(dst) == visited.end()) {
                visited.insert(dst);
                totalweight = totalweight + w;
            }

            // add outgoing edges from dst to unvisited vertices to the minheap
            for (std::tuple<int,int> e: graph[dst]) {
                int weight = get<0>(e);
                int v = get<1>(e);
                if (visited.find(v) == visited.end()) {
                    minheap.push(std::make_tuple(-1*weight, v));
                }
            }
        }

        // return totalweight or -1 if not all vertices were visited
        if (visited.size() == n) {
            return totalweight;
        }
        return -1;

        // Time complexity is O(ElogE) because in the worst case we have to push and pop E edges from the graph.
        // pushing and popping is worst case O(logE) so total is O(ElogE)
    }
};

