"""
Design a Double-ended Queue class.

Your Deque class should support the following operations:

Deque() will initialize an empty queue.
bool isEmpty() will return whether the queue is empty or not.
void append(int value) will insert value at the end of the queue.
void appendleft(int val) will insert value at the beginning of the queue.
int pop() will remove and return the value at the end of the queue. If the queue is empty, return -1.
int popleft() will remove and return the value at the beginning of the queue. If the queue is empty, return -1.
Note: You should implement each operation in  O(1) time complexity.
"""

class Node:

    def __init__(self, value, next_node = None, prev_node = None):
        self.val = value
        self.next = next_node
        self.prev = prev_node

class Deque:
    
    def __init__(self):
        self.head = Node(-1)
        self.tail = Node(-1)
        self.head.next = self.tail
        self.tail.prev = self.head

    def isEmpty(self) -> bool: # This will be used for checking emptiness before popping
        if self.head.next == self.tail:
            return True
        else:
            return False
        
    def append(self, value: int) -> None: # Insert a value at the end (before tail)
        node = Node(value, self.tail, self.tail.prev)
        node.prev.next = node
        self.tail.prev = node
        
    def appendleft(self, value: int) -> None: # Insert a value at the beginning (after head)
        node = Node(value, self.head.next, self.head)
        node.next.prev = node
        self.head.next = node
        
    def pop(self) -> int: # remove and return value at the tail, if empty return -1
        if self.isEmpty():
            return -1
        else:
            remove = self.tail.prev
            v = remove.val
            self.tail.prev = remove.prev
            remove.prev.next = self.tail
            del remove
            return v

    def popleft(self) -> int: # remove and return value at the head, if empty return -1
        if self.isEmpty():
            return -1
        else:
            remove = self.head.next
            v = remove.val
            self.head.next = remove.next
            remove.next.prev = self.head
            del remove
            return v
        
""" 
Double ended queue: Need to insert and pop from the beginning and end of the queue 
in O(1) time complexity. To achieve this we can implement a doubly linked list. ListNodes will
have a val, next pointer, and previous pointer. Initializing the empty queue will 
initialize a dummy head and tail that point to each other. If the head's next pointer points
to the tail, the list is empty. When appending we have to reorganize pointers. When popping,
first we will check if the queue is empty and then we will reorganize pointers.

Input:
["isEmpty", "append", 10, "isEmpty", "appendLeft", 20, "popLeft", "pop", "pop", "append", 30, "pop", "isEmpty"]

Output:
[true, null, false, null, 20, 10, -1, null, 30, true]
"""