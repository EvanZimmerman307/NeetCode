/* Design a Dynamic Array (aka a resizable array) class, such as an ArrayList in Java or a vector in C++.

Your DynamicArray class should support the following operations:

DynamicArray(int capacity) will initialize an empty array with a capacity of capacity, where capacity > 0.
int get(int i) will return the element at index i. Assume that index i is valid.
void set(int i, int n) will set the element at index i to n. Assume that index i is valid.
void pushback(int n) will push the element n to the end of the array.
int popback() will pop and return the element at the end of the array. Assume that the array is non-empty.
void resize() will double the capacity of the array.
int getSize() will return the number of elements in the array.
int getCapacity() will return the capacity of the array.
If we call void pushback(int n) but the array is full, we should resize the array first. */

#include <iostream>
#include <algorithm> // For std::copy

class DynamicArray {
public:

    int length;
    int* dynamic_array;
    int num_elements;

    DynamicArray(int capacity) {
        length = capacity;
        dynamic_array = new int[capacity];
        num_elements = 0;
        // Might need to add some version of num_elements

    }

    int get(int i) { // will return the element at index i. Assume that index i is valid.
        return dynamic_array[i];

    }

    void set(int i, int n) { //will set the element at index i to n. Assume that index i is valid.
        dynamic_array[i] = n;

    }

    void pushback(int n) { //will push the element n to the end of the array.
        //if the array is full, we should resize the array first.
        if (num_elements == length) {
            resize();
        }
        dynamic_array[num_elements] = n;
        num_elements++;
    }

    int popback() { //pop and return the element at the end of the array. Assume that the array is non-empty.
        int val = dynamic_array[num_elements - 1];
        dynamic_array[num_elements - 1] = 0;
        num_elements--;
        return val;

    }

    void resize() {
        int* new_array = new int[length * 2]; //allocating the new array
        std::copy(dynamic_array, dynamic_array + length, new_array); // Copy elements
        
        delete[] dynamic_array; // Free old array memory
        dynamic_array = new_array; // point to the new array

        length = length * 2; //update the capacity


    }

    int getSize() { //will return the number of elements in the array.
        return num_elements;

    }

    int getCapacity() { //will return the capacity of the array.
        return length;

    }
};

/* Input:
["Array", 1, "getSize", "getCapacity", "pushback", 1, "getSize", "getCapacity", 
 "pushback", 2, "getSize", "getCapacity", "get", 1, "set", 1, 3, "get", 1, "popback", "getSize", "getCapacity"]

Output:
[null, 0, 1, null, 1, 1, null, 2, 2, 2, null, 3, 3, 1, 2] */



