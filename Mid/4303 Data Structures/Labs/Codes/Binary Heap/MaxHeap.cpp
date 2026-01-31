// MaxHeap

#include <bits/stdc++.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class MH
{
    int size = 0;

    int *arr;

    int capacity;

public:
    MH(int capacity)
    {
        this->capacity = capacity;
        arr = new int[capacity];
        size = 0;
    }

    ~MH()
    {
        delete[] arr;
    }

    int parent(int idx)
    {
        return (idx - 1) / 2;
    }

    int left(int idx)
    {
        return (2 * idx) + 1;
    }

    int right(int idx)
    {
        return (2 * idx) + 2;
    }

    int getMax()
    {
        return arr[0];
    }

    void bubbleUp(int idx)
    {
        while (idx != 0 && arr[parent(idx)] < arr[idx])
        {
            swap(&arr[idx], &arr[parent(idx)]);
            idx = parent(idx);
        }
    }

    void heapify(int idx)
    {
        int largest_idx = idx;

        if (left(idx) < size && arr[largest_idx] < arr[left(idx)])
        {
            largest_idx = left(idx);
        }

        if (right(idx) < size && arr[largest_idx] < arr[right(idx)])
        {
            largest_idx = right(idx);
        }

        if (largest_idx != idx)
        {
            swap(&arr[idx], &arr[largest_idx]);
            heapify(largest_idx);
        }
    }

    void insertKey(int val)
    {
        if (size == capacity)
        {
            std::cout << "\nOverflow";
            return;
        }

        int idx = size;
        arr[size++] = val;

        bubbleUp(idx);
    }

    void increaseKey(int idx, int byVal)
    {
        if (byVal < 0)
        {
            decreaseKey(idx, -byVal);
            return;
        }
        arr[idx] += byVal;
        bubbleUp(idx);
    }

    void decreaseKey(int idx, int byVal)
    {

        if (byVal < 0)
        {
            increaseKey(idx, -byVal);
            return;
        }
        arr[idx] -= byVal;
        heapify(idx);
    }

    int extractMax()
    {
        if (size == 0)
            return INT_MIN;
        if (size == 1)
        {
            return arr[--size];
        }

        int root = arr[0];
        arr[0] = arr[--size];

        heapify(0);
        return root;
    }

    int deleteKey(int idx)
    {
        if (size == 0 || idx >= size)
            return INT_MIN;
        if (size == 1)
        {
            return arr[--size];
        }

        int root = arr[idx];
        arr[idx] = arr[--size];

        if (arr[idx] > arr[parent(idx)] && idx != 0)
            bubbleUp(idx);
        else
            heapify(idx);
        return root;
    }
};

int main()
{
    // Quick Test
    MH h(10);
    h.insertKey(10);
    h.insertKey(20);
    h.insertKey(15);
    h.insertKey(40);
    h.insertKey(50);

    // Heap: 50, 40, 15, 10, 20
    std::cout << "Max: " << h.getMax() << "\n";

    h.deleteKey(0);

    std::cout << "Max after delete: " << h.getMax() << "\n";
    return 0;
}