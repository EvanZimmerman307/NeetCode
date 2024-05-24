""" Design a Dynamic Array (aka a resizable array) class, such as an ArrayList in Java or a vector in C++.

Your DynamicArray class should support the following operations:

DynamicArray(int capacity) will initialize an empty array with a capacity of capacity, where capacity > 0.
int get(int i) will return the element at index i. Assume that index i is valid.
void set(int i, int n) will set the element at index i to n. Assume that index i is valid.
void pushback(int n) will push the element n to the end of the array.
int popback() will pop and return the element at the end of the array. Assume that the array is non-empty.
void resize() will double the capacity of the array.
int getSize() will return the number of elements in the array.
int getCapacity() will return the capacity of the array.
If we call void pushback(int n) but the array is full, we should resize the array first. """


class DynamicArray:
    
    def __init__(self, capacity: int):
        self.array = [None] * capacity
        self.num_elements = 0
        self.capacity = capacity


    def get(self, i: int) -> int:
        return self.array[i]

    def set(self, i: int, n: int) -> None:
        self.array[i] = n

    def pushback(self, n: int) -> None:
        if self.num_elements == len(self.array):
            self.resize()
        self.array[self.num_elements] = n
        self.num_elements += 1
        print(self.array)

    def popback(self) -> int:
        val = self.array[self.num_elements - 1]
        self.array[self.num_elements - 1] = None
        self.num_elements -= 1
        return val
 

    def resize(self) -> None: #When you resize it you have to double the capacity
        self.array = self.array + [None] * self.capacity
        self.capacity *= 2


    def getSize(self) -> int:
        return self.num_elements # will return the number of elements in the array.


    def getCapacity(self) -> int:
        return len(self.array)


""" Input:
["Array", 1, "getSize", "getCapacity", "pushback", 1, "getSize", "getCapacity", 
 "pushback", 2, "getSize", "getCapacity", "get", 1, "set", 1, 3, "get", 1, "popback", "getSize", "getCapacity"]

Output:
[null, 0, 1, null, 1, 1, null, 2, 2, 2, null, 3, 3, 1, 2] """
