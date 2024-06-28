#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    std::vector<int> topologicalSort(int n, std::vector<std::vector<int>>& edges) {
        /*
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
        */
        
        // build adjacency list
        std::unordered_map<int, std::vector<int>> graph;
        for (auto e: edges) {
            int u = e[0];
            int v = e[1];
            graph[u].push_back(v);
        }

        // setup topological sort
        std::unordered_set<int> visited;
        std::unordered_set<int> path;
        std::vector<int> topsort;

        // dfs on every vertex
        for (int i = 0; i < n; i++) {
            bool success = dfs(i, graph, visited, path, topsort);
            if (!success) {
                std::vector<int> emptyvec;
                return emptyvec;
            }
        }

        // reverse the topsort to get the correct ordering
        std::reverse(topsort.begin(), topsort.end());
        return topsort;
    }

    bool dfs(int vertex, std::unordered_map<int, std::vector<int>>& graph, std::unordered_set<int>& visited,
        std::unordered_set<int>& path, std::vector<int>& topsort) {
            // if we have already added a vertex to our topological sort, return true
            if (visited.find(vertex) != visited.end()) {
                return true;
            }
            // we have detected a cycle 
            if (path.find(vertex) != path.end()) {
                return false;
            }

            path.insert(vertex);
            // call dfs on adjacent vertices 
            for (auto v: graph[vertex]) {
                bool success = dfs(v, graph, visited, path, topsort);
                if (!success) {
                    return false;
                }
            }
            // add vertex to topsort after processing adjacent vertices, mark as visited, remove from path so it is reachable from other dfs
            topsort.push_back(vertex);
            visited.insert(vertex);
            path.erase(vertex);
            return true;
        }

        //Time Complexity is O(V+E) because in the worst case we have to process every node and edge.
};
