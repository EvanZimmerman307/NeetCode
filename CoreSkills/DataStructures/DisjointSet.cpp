/*
Design a Disjoint Set (aka Union-Find) class.

Your UnionFind class should support the following operations:

UnionFind(int n) will initialize a disjoint set of size n.
int find(int x) will return the root of the component that x belongs to.
bool isSameComponent(int x, int y) will return whether x and y belong to the same component.
bool union(int x, int y) will union the components that x and y belong to. If they are already in the same component, return false, otherwise return true.
int getNumComponents() will return the number of components in the disjoint set.

With proper path compression and union by rank/size, 
every operation should be O(1) in the average case.
*/
#include <vector>

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

/*
Input:
["UnionFind", 10, "isSameComponent", 1, 3, "union", 1, 2, "union", 2, 3, "getNumComponents", "isSameComponent", 1, 3]

Output:
[null, 1, false, true, true, 8, true]
*/