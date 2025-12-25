#include <bits/stdc++.h>

using namespace std;

// maxValue_Priority queue (Priority proportional to value)

#define Size 7

int arr[Size];

int cur_size = 0;

int max_priority = INT16_MIN;

bool isFull()
{
    if (cur_size == Size)
        return true;
    return false;
}

bool isEmpty()
{
    if (!cur_size)
        return true;
    return false;
}

void reset()
{
    cur_size = 0;
    return;
}

void evaluateNewPriority()
{
    if (isEmpty())
        return;

    max_priority = INT_MIN;
    for (int i = 0; i < cur_size; i++)
    {
        max_priority = max(max_priority, arr[i]);
    }
    return;
}

int enqueue(int x)
{
    if (isFull())
    {
        cout << "Queue is Full" << '\n';
        return -1;
    }

    arr[cur_size] = x;
    max_priority = max(max_priority, x);
    cur_size++;
    return 0;
}

int dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << '\n';
        return -1;
    }

    int i;
    for (i = 0; i < cur_size; i++)
    {
        if (max_priority == arr[i])
            break;
    }

    int returnValue = arr[i];

    // shifting the arr
    for (int j = i; j < cur_size - 1; j++)
    {
        arr[j] = arr[j + 1];
    }

    cur_size--;

    evaluateNewPriority();

    return returnValue;
}

int peek()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << '\n';
        return -1;
    }
    return max_priority;
}