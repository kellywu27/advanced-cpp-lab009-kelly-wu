// created a main.cpp to fix error
#include <iostream>

#include "project/heap.h"

int main() {
    MaxHeap heap(std::vector<int>{5, 3, 8, 1, 9, 2});
    heap.push(7);

    std::cout << "Top: " << heap.top() << "\nSize: " << heap.size() << '\n';
    std::cout << "Sorted:";
    for (int value : heap.heapSort()) {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
    return 0;
}