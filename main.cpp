#include <iostream>
#include <vector>
#include <chrono>


class DynamicArray {
private:
    int *array;
    int capacity;
    int size_arr;

public:
    DynamicArray() {
        capacity = 4;
        size_arr = 0;
        array = new int[capacity];
    }

    ~DynamicArray() {
        delete[] array;
    }

    int& operator[](int index) {
        if (index >= 0 && index < size_arr) {
            return array[index];
        }
        throw std::out_of_range("Index out of range");
    }

    int getSize(){
        return size_arr;
    }

    void append(int value) {
        if (size_arr == capacity) {
            resize(2 * capacity);
        }
        array[size_arr++] = value;
    }

    void remove(int index) {
        if (index >= 0 && index < size_arr) {
            for (int i = index; i < size_arr - 1; ++i) {
                array[i] = array[i + 1];
            }
            size_arr--;

            if (size_arr < capacity / 4) {
                resize(capacity / 2);
            }
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    void push_back(int value) {
        append(value);
    }

    void pop_back() {
        if (size_arr > 0) {
            size_arr--;

            if (size_arr < capacity / 4) {
                resize(capacity / 2);
            }
        } else {
            throw std::out_of_range("Array is empty");
        }
    }

    void insert(int position, const int* begin, const int* end) {
        int elements_to_insert = end - begin;
        if (position >= 0 && position <= size_arr) {
            if (size_arr + elements_to_insert > capacity) {
                resize(std::max(2 * capacity, size_arr + elements_to_insert));
            }

            for (int i = size_arr - 1; i >= position; --i) {
                array[i + elements_to_insert] = array[i];
            }

            for (int i = 0; i < elements_to_insert; ++i) {
                array[position + i] = begin[i];
            }

            size_arr += elements_to_insert;
        } else {
            throw std::out_of_range("Invalid position for insertion");
        }
    }

    void erase(int position, int count) {
        if (position >= 0 && position < size_arr && count >= 0) {
            int elements_to_erase = std::min(count, size_arr - position);

            for (int i = position; i < size_arr - elements_to_erase; ++i) {
                array[i] = array[i + elements_to_erase];
            }

            size_arr -= elements_to_erase;

            if (size_arr < capacity / 4) {
                resize(capacity / 2);
            }
        } else {
            throw std::out_of_range("Invalid position or count for erasure");
        }
    }

private:
    void resize(int new_capacity) {
        int *new_array = new int[new_capacity];
        for (int i = 0; i < size_arr; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        capacity = new_capacity;
    }
};

int main() {
    const int numOperations = 1000000;  // Adjust as needed

    // Test DynamicArray
    {
        DynamicArray dynamicArray;

        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numOperations; ++i) {
            dynamicArray.push_back(i);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        std::cout << "DynamicArray append time: " << elapsed_time << " microseconds\n";
    }

    // Test std::vector
    {
        std::vector<int> stdVector;

        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numOperations; ++i) {
            stdVector.push_back(i);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        std::cout << "std::vector append time: " << elapsed_time << " microseconds\n";
    }

    return 0;
}
