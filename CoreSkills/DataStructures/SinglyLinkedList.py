"""Design a Singly Linked List class.

Your LinkedList class should support the following operations:

LinkedList() will initialize an empty linked list.
int get(int i) will return the value of the ith node (0-indexed). If the index is out of bounds, return -1.
void insertHead(int val) will insert a node with val at the head of the list.
void insertTail(int val) will insert a node with val at the tail of the list.
int remove(int i) will remove the ith node (0-indexed). If the index is out of bounds, return false, otherwise return true.
int[] getValues() return an array of all the values in the linked list, ordered from head to tail."""

class ListNode:
    def __init__(self, val, next_node = None): # pointers going from head to tail
        self.val = val
        self.next_node = next_node

class LinkedList:
    
    def __init__(self): # O(1)
        self.head = ListNode(-1) # dummy node, no next_node
        self.tail = self.head # head is last node in LinkedList at start

    def get(self, index: int) -> int: # O(N) 
        #Traverse the list until we reach the target index
        node = self.head.next_node
        i = 0
        while node:
            print("i: ", i, " Val: ", node.val)
            if i == index:
                return node.val
            i += 1
            node = node.next_node
        print("Get index out of bounds")
        return -1

    def insertHead(self, val: int) -> None: # O(1)
        node = ListNode(val, next_node = self.head.next_node)
        self.head.next_node = node
        #If the head is the tail
        if self.tail == self.head:
            self.tail = node
        
    def insertTail(self, val: int) -> None: # O(1)
        node = ListNode(val)
        self.tail.next_node = node
        self.tail = node
        
    def remove(self, index: int) -> bool: # O(N)
        #Traverse the list until we reach the node right before the index
        node = self.head
        i = -1
        while node.next_node: # While there is a next node we could remove
            if i == index - 1: # We reach the node before the one we want to remove
                #Could be removing the tail, so update
                if node.next_node == self.tail:
                    self.tail = node

                remove = node.next_node.val
                node.next_node = node.next_node.next_node
                print("Removed: ", remove)
                return True
            i += 1
            node = node.next_node
        return False

    def getValues(self) -> list[int]: # O(N)
        values = []
        #Traverse the list
        node = self.head.next_node
        i = 0
        while node:
            values.append(node.val)
            i += 1
            node = node.next_node
        return values

"""Input: 
["insertHead", 1, "insertTail", 2, "insertHead", 0, "remove", 1, "getValues"]

Output:
[null, null, null, true, [0, 2]]
"""
        
