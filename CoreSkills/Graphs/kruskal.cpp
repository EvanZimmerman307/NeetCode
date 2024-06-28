#include <queue>
#include <tuple>

class UnionFind {
public:
    std::vector<int> parents;
    std::vector<int> size;
    int num_components;

    UnionFind(int n) {
        num_components = n;
        for (int i = 0; i < n; i++) {
            parents.push_back(i);
            size.push_back(1);
        }
    }

    int find(int x) { // return the root of the component that x belongs to.
        while (x != parents[x]){
            parents[x] = find(parents[x]);
            x = parents[x];
        }
        return parents[x];

    }

    bool isSameComponent(int x, int y) { // return whether x and y belong to the same component.
        if (find(x) == find(y)){
            return true;
        }
        return false;

    }

    // Union is a reserved keyword in C++, so we use _union instead
    bool _union(int x, int y) { // union the components that x and y belong to
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) {
                parents[rootX] = rootY;
                size[rootY] = size[rootY] + size[rootX];
            }
            else {
                parents[rootY] = rootX;
                size[rootX] = size[rootX] + size[rootY];
            }
            num_components--;
            return true;
        }
        return false; // x and y belong to the same component
    }

    int getNumComponents() {
        return num_components;
    }
};

class Solution {
public:
    int minimumSpanningTree(std::vector<std::vector<int>>& edges, int n) {
            /*
            - implement kruskal's MST algo
            - minimum spanning tree (MST) is the set of edges that connects all the vertices in an undirected graph for the lowest total cost
            - MSTs can not have cycles
            - kruskal's algo: use the unionfind data structure to manage connecting the graph, put all the edges on a min heap
            - pop off the min edge, union the vertices if possible, unionfind ensures we don't union vertices already connected
            - return the total weight or -1 if unconnected graph.
            - n: number of vertices, vertices are labeled 0 to n-1
            - edges: list of tuples (u,v,w) where u and v are vertices and w is the weight

            Input:
            n = 5
            edges = [[0,1,10], [0,2,3], [1,3,2], [2,1,4], [2,3,8], [2,4,2], [3,4,5]]

            Output:
            11
            */

            // setup kruskal's
        UnionFind unionfind = UnionFind(n); // to start, each vertex is its own component
        std::priority_queue<std::tuple<int,int,int>> minheap;
        for (auto e: edges) { // loop through edges and add to minheap
            int u = e[0];
            int v = e[1];
            int w = e[2];
            minheap.push(std::make_tuple(-1 * w, u, v));
        }
        int totalweight = 0;
        int mst_edges = 0;

        while (!minheap.empty()) {
            // pop the edge of lowest cost off the minheap
            auto edge = minheap.top();
            minheap.pop();
            int w = get<0>(edge);
            int u = get<1>(edge);
            int v = get<2>(edge);
            w = w * -1; // get weight back to positive number

            // try to union the two vertices of the edge
            bool connected = unionfind._union(u,v);
            if (connected ==  true) {
                totalweight = totalweight + w;
                mst_edges++;
                if (mst_edges == n-1) { // mst is formed when we have n - 1 edges
                    return totalweight;
                }
            }
        }
        return -1;
        // Time Complexity: pushing and popping from the minheap will have bigger impact than union find.
        // O(ElogE) because worst case we push and pop (logE) E edges from the minheap.
    }
};
