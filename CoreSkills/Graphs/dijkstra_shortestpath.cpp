#include <unordered_map>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_set>

class Solution {
public:
    std::unordered_map<int, int> shortestPath(int n, std::vector<std::vector<int>>& edges, int src) {
        /*
        - return the shortest distance from the starting vertex to every other vertex
        - dijkstra's algorithm: greedy algo - put edges on a minheap and pop off edges with min total cost
        - if a vertex is unreachable it's shortest path distance is -1

        Input:
        n = 5 (number of vertices)
        edges = [[0,1,10], [0,2,3], [1,3,2], [2,1,4], [2,3,8], [2,4,2], [3,4,5]] (u, v, w) (start, dst, weight)
        src = 0 (starting vertex)

        Output:
        {{0:0}, {1:7}, {2:3}, {3:9}, {4:5}}

        */

        std::unordered_map<int,int> shortestpaths; //key: vertex, value: shortest path distance
        for (int i = 0; i < n; i++) {
            shortestpaths[i] = -1;
        }

        // 1. Building adjacency list
        std::unordered_map<int, std::vector<std::tuple<int,int>>> graph;
        for (int i = 0; i < edges.size(); i++) {
            int v = edges[i][0]; // src
            int u = edges[i][1]; // dst
            int w = edges[i][2]; // weight
            graph[v].push_back(std::make_tuple(w, u));
        }

        // 2. Setup dijkstra's
        std::unordered_set<int> visited;
        std::priority_queue<std::tuple<int,int>> minheap; // tuple(total cost, dst vertex), first element of tuple is treated as priority
        // priority queues are maxheaps by default -> negate weight of edges to achieve a minheap
        visited.insert(src);
        for (int i = 0; i < graph[src].size(); i++) {
            // push the outgoing edges from src onto the minheap
            int weight = get<0>(graph[src][i]);
            int dst = get<1>(graph[src][i]);
            minheap.emplace(-weight, dst); // or could minheap.push(std::make_tuple())
        }
        shortestpaths[src] = 0;

        // 3. execute dijkstra's
        while(!minheap.empty()) {
            std::tuple<int,int> edge = minheap.top();
            int weight = get<0>(edge);
            int dst = get<1>(edge);
            minheap.pop();
            weight = weight * -1; // convert back to positive weight

            // if the dst is not visited, update shortestpaths
            if (visited.find(dst) == visited.end()) {
                visited.insert(dst);
                shortestpaths[dst] = weight;
            }

            // add edges from dst to unvisited vertices
            for (std::tuple<int,int> edge : graph[dst]) { // looping through the outgoing edges of dst vertex
                int w = get<0>(edge);
                int v = get<1>(edge);
                if (visited.find(v) == visited.end()) {
                    minheap.emplace(-1*(w + shortestpaths[dst]), v);
                }
            }
        }

        return shortestpaths;

        // Time Complexity: O(ElogE) because for E edges we have to push and pop them from the minheap which takes logE time.





        


        
    }
};
