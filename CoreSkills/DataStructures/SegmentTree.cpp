/*
Design a Segment Tree class.

Your SegmentTree class should support the following operations:

SegmentTree(int[] arr) will initialize a segment tree based on the given array arr. You can assume that the array arr is non-empty.
int query(int l, int r) will return the sum of all elements in the range [l, r] inclusive. You can assume that 0 <= l <= r < arr.length.
void update(int idx, int val) will update the element at index idx in the original array to be val. You can assume that 0 <= idx < arr.length.
*/

#include <vector>

class SegmentNode {
public:
    int sum;
    int start;
    int end;
    SegmentNode* left = nullptr;
    SegmentNode* right = nullptr;
    int mid;

    SegmentNode(int total, int st, int en, int middle) {
        sum = total;
        start = st;
        end = en;
        mid = middle;
    }
};

class SegmentTree {
public:
    std::vector<int> values;
    SegmentNode* root;

    SegmentTree(std::vector<int>& nums) {
        values = nums;
        root = build_tree(0, nums.size()-1);

    }

    SegmentNode* build_tree(int start, int end) { //recursive O(n)
        if (start == end) {
            return new SegmentNode(values[start], start, end, 0);
        }

        int middle = (start + end) / 2;
        SegmentNode* node = new SegmentNode(0, start, end, middle);

        node->left = build_tree(start, node->mid);
        node->right = build_tree(node->mid + 1, end);
        node->sum = node->left->sum + node->right->sum;
        return node;
    }

    
    void update(int index, int val) { //recursive O(logn)
        // will update the element at index in the original array to be val
        updateHelper(root, index, val);
        return;
    }

    void updateHelper(SegmentNode* node, int index, int val) { // recurisve O(logn)
        if (node->start == index && node->end == index) {
            node->sum = val;
            return;
        }

        if (index <= node->mid) {
            updateHelper(node->left, index, val);
        }
        else {
            updateHelper(node->right, index, val);
        }
        node->sum = node->left->sum + node->right->sum;
        return;
    }
    
    int query(int L, int R) { //recursive O(logn)
        // Traverse the segment tree until we reach the node that corresponds to our range
        return queryHelper(root, L, R);

    }

    int queryHelper(SegmentNode* node, int start, int end) {
        if (node->start == start && node->end == end) {
            return node->sum;
        }

        if (end <= node->mid) { // query left
            return queryHelper(node->left, start, end);
        }
        else if (start >= node->mid + 1) { // query right
            return queryHelper(node->right, start, end);
        }
        else{
            return queryHelper(node->left, start, node->mid) + queryHelper(node->right, node->mid + 1, end);
        }
    }
};

/*
Input:
["SegmentTree", [1, 2, 3, 4, 5], "query", 0, 2, "query", 2, 4, "update", 3, 0, "query", 2, 4]

Output:
[null, 6, 12, null, 8]

Input:
["SegmentTree", [-1, 2, 4], "query", 0, 1, "query", 1, 2, "update", 2, 3, "query", 0, 2]

Output:
[null, 1, 6, null, 4]
*/
