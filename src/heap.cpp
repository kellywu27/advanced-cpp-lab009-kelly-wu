#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void MaxHeap::push(int value) {
    (void)value;
    // append @ the end then restore heap order upward
    data_.push_back(value);
    heapifyUp(data_.size() - 1);
}

int MaxHeap::pop() {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    // move last element to root, shrink, then restore order downward
    const int maxValue = data_.front();
    data_.front() = data_.back();
    data_.pop_back();
    if (!data_.empty()) {
        heapifyDown(0);
    }
    return maxValue;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    (void)values;
    // bottom-up construct in O(n)
    data_ = values;
    for (std::size_t i = data_.size() / 2; i-- > 0;) {
        heapifyDown(i);
    }
}

std::vector<int> MaxHeap::heapSort() {
    // repeatedly pop max from copy, then reverse descending output to get ascending order
    MaxHeap working = *this;
    std::vector<int> sorted;
    sorted.reserve(working.size());
    while (!working.empty()) {
        sorted.push_back(working.pop());
    }
    std::reverse(sorted.begin(), sorted.end());
    return sorted;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    (void)index;
    // swap w/ parent while node > its parent
    while (index > 0 && data_[parentIndex(index)] < data_[index]) {
        swap(data_[parentIndex(index)], data_[index]);
        index = parentIndex(index);
    }
}

void MaxHeap::heapifyDown(std::size_t index) {
    (void)index;
    // swap w/ larger child while child > node
   while (true) {
        const std::size_t left = leftChildIndex(index);
        const std::size_t right = rightChildIndex(index);
        std::size_t largest = index;
        if (left < data_.size() && data_[largest] < data_[left]) {
            largest = left;
        }
        if (right < data_.size() && data_[largest] < data_[right]) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        swap(data_[index], data_[largest]);
        index = largest;
    }
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}