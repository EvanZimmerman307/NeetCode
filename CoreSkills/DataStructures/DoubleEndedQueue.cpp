/*
Design a Double-ended Queue class.

Your Deque class should support the following operations:

Deque() will initialize an empty queue.
bool isEmpty() will return whether the queue is empty or not.
void append(int value) will insert value at the end of the queue.
void appendleft(int val) will insert value at the beginning of the queue.
int pop() will remove and return the value at the end of the queue. If the queue is empty, return -1.
int popleft() will remove and return the value at the beginning of the queue. If the queue is empty, return -1.
Note: You should implement each operation in  O(1) time complexity.
*/

class Node {
public:
    int val;
    Node* next;
    Node* prev;

    Node(int value, Node* next_node = nullptr, Node* prev_node = nullptr) {
        val = value;
        next = next_node;
        prev = prev_node;
    }

};

class Deque {
public:
    Node* head;
    Node* tail;

    Deque() {
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
        tail->prev = head;
    }

    bool isEmpty() {
        if (head->next == tail) {
            return true;
        }
        else {
            return false;
        }

    }

    void append(int value) { //insert value at the tail
        Node* node = new Node(value, tail, tail->prev);
        tail->prev = node;
        node->prev->next = node;
    }

    void appendleft(int value) { //insert at the head of the queue
        Node* node = new Node(value, head->next, head);
        head->next = node;
        node->next->prev = node;
    }

    int pop() { //remove and return val at the tail, if empty return -1
        if (isEmpty()) {
            return -1;
        }
        else {
            Node* remove = tail->prev;
            int v = remove->val;
            tail->prev = remove->prev;
            remove->prev->next = tail;
            delete remove;
            return v;
        }
        
    }

    int popleft() { //remove and return val at the head, if empty return -1
        if (isEmpty()) {
            return -1;
        }
        else {
            Node* remove = head->next;
            int v = remove->val;
            head->next = remove->next;
            remove->next->prev = head;
            delete remove;
            return v;
        }
    }
};

/* 
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
*/


