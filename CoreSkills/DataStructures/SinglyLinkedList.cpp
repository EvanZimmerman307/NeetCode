/*Design a Singly Linked List class.

Your LinkedList class should support the following operations:

LinkedList() will initialize an empty linked list.
int get(int i) will return the value of the ith node (0-indexed). If the index is out of bounds, return -1.
void insertHead(int val) will insert a node with val at the head of the list.
void insertTail(int val) will insert a node with val at the tail of the list.
int remove(int i) will remove the ith node (0-indexed). If the index is out of bounds, return false, otherwise return true.
int[] getValues() return an array of all the values in the linked list, ordered from head to tail.*/

#include <iostream>
#include <vector>

class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int v, ListNode* next_ptr = NULL) { //O(1)
        val = v;
        next = next_ptr;
    }
};

class LinkedList {
public:
    ListNode* head;
    ListNode* tail;

    LinkedList() { // O(1)
        head = new ListNode(-1);
        tail = head;
    }

    int get(int index) { // O(N)
        ListNode* node = head->next;
        int i = 0;
        while (node != NULL) {
            if (i == index) {
                return node->val;
            }
            i ++;
            node = node->next;
        }
        return -1;
    }

    void insertHead(int val) { //O(1)
        ListNode* node = new ListNode(val, head->next);
        head->next = node;
        if (head == tail) { // If the list is empty
            tail = node;
        }
        std::cout << "Insert head: " << node->val << std::endl;
    }
    
    void insertTail(int val) { //O(1)
        ListNode* node = new ListNode(val);
        tail->next = node;
        tail = node;
        std::cout << "Insert tail: " << node->val << std::endl;
    }

    bool remove(int index) { //O(N) - traverse the list until the index before removal
        ListNode* node = head;
        int i = -1;
        while (node->next != NULL) { 
            if (i == index - 1) {
                if (node->next == tail) { //if we are removing the tail, need to reassign tail
                    tail = node;
                }
                ListNode* remove = node->next;
                node->next = remove->next;
                std::cout << "Remove: " << remove->val << std::endl;
                delete remove;
                return true;
            }
            i++;
            node = node->next;
        }
        return false;
    }

    std::vector<int> getValues() { //O(N)
        std::vector<int> v;
        ListNode* node = head->next;
        while (node != NULL) {
            v.push_back(node->val);
            node = node->next;
        }
        return v;
    }
};

/*Input: 
["insertHead", 1, "insertTail", 2, "insertHead", 0, "remove", 1, "getValues"]

Output:
[null, null, null, true, [0, 2]]
*/