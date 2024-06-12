"""
Design a Segment Tree class.

Your SegmentTree class should support the following operations:

SegmentTree(int[] arr) will initialize a segment tree based on the given array arr. You can assume that the array arr is non-empty.
int query(int l, int r) will return the sum of all elements in the range [l, r] inclusive. You can assume that 0 <= l <= r < arr.length.
void update(int idx, int val) will update the element at index idx in the original array to be val. You can assume that 0 <= idx < arr.length.
"""

class segmentNode:

    def __init__(self, leftInd, rightInd, total, middle = None):
        self.total = total
        self.start = leftInd
        self.end = rightInd
        self.left = None
        self.right = None
        self.mid = middle

class SegmentTree:
    
    def __init__(self, nums: list[int]):
        self.arr = nums
        self.root = self.build_tree(0, len(self.arr) - 1)
    
    def build_tree(self, start: int, end: int) -> segmentNode: # recursive O(n)
        # Basecase: range is just one index, make leaf node
        print("start: ", start, "end: ", end)
        if start == end:
            return segmentNode(start, end, self.arr[start])
        else: # building tree on left,Mid and Mid+1,right
            mid = (end + start) // 2
            node = segmentNode(start, end, 0, mid)
            node.left = self.build_tree(start, mid)
            node.right = self.build_tree(mid + 1, end)
            node.total = node.left.total + node.right.total
            return node
        
    def update(self, index: int, val: int) -> None: #O(logn)
        self.updateHelper(self.root, index, val)
        return
    
    def updateHelper(self, node: segmentNode, index: int, val: int) -> None: # O(logn)
        if node.start == index and node.end == index: # reached the leaf, range corresponds to single index
            node.total = val
            return
        else:
            if index <= node.mid:
                self.updateHelper(node.left, index, val)
            else:
                self.updateHelper(node.right, index, val)
            node.total = node.right.total + node.left.total
            return
    
    def query(self, L: int, R: int) -> int: # O(logn)
        return self.queryHelper(self.root, L, R)
    
    def queryHelper(self, node: segmentNode, L: int, R: int) -> int: # O(logn)
        # Basecase: found the node that corresponds to our segment
        if node.start == L and node.end == R:
            return node.total
        else:
            if R <= node.mid: # go left
                return self.queryHelper(node.left, L, R)
            elif L > node.mid: # go right
                return self.queryHelper(node.right, L, R)
            else: # query spans left and right
                return self.queryHelper(node.left, L, node.mid) + self.queryHelper(node.right, node.mid+1, R)

"""
Input:
["SegmentTree", [1, 2, 3, 4, 5], "query", 0, 2, "query", 2, 4, "update", 3, 0, "query", 2, 4]

Output:
[null, 6, 12, null, 8]

Input:
["SegmentTree", [-1, 2, 4], "query", 0, 1, "query", 1, 2, "update", 2, 3, "query", 0, 2]

Output:
[null, 1, 6, null, 4]
"""
        

