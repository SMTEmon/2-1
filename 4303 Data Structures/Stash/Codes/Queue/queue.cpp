#include <bits/stdc++.h>

using namespace std;

// normal queue

#define Size 7

int arr[Size];

int front = -1;
int rear = -1;

bool isFull()
{
    if (rear == Size - 1)
        return true;
    return false;
}

bool isEmpty()
{
    if (front == -1)
        return true;
    return false;
}

void reset()
{
    front = -1;
    rear = -1;
}

int enqueue(int x)
{
    if (isFull())
    {
        cout << "Queue is Full" << '\n';
        return -1;
    }

    if (rear == -1 && front == -1)
        front++;

    rear++;
    arr[rear] = x;
    return 0;
}

int dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << '\n';
        return -1;
    }
    arr[front] = 0;
    front++;
    if (front > rear)
    {
        cout << "Array is Empty now, Reseting" << '\n';
        reset();
    }
    return 0;
}

int peek()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << '\n';
        return -1;
    }
    return arr[front];
}