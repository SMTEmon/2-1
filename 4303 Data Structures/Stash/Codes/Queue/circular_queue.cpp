#include <bits/stdc++.h>

using namespace std;

// Circular Queue
#define Capacity 10

int arr[Capacity];

int front = -1;
int rear = -1;
int Size_rn = 0; // not used here

bool isEmpty()
{
    if (front == -1)
        return true;
    return false;
}

bool isFull()
{
    if (((rear + 1) % Capacity == front))
        // use ((rear + 1) % Capacity == front) only for one-spot-sacrifice
        // use (Size_rn == Capacity) in general
        return true;
    return false;
}

int enqueue(int x)
{
    if (isFull())
    {
        cout << "Queue is Full" << '\n';
        return -1;
    }
    if (front == -1 && rear == -1)
    {
        front++;
    }
    rear = (rear + 1) % Capacity;
    arr[rear] = x;
    Size_rn++; // not used here
    return 0;
}

int dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is Empty" << '\n';
        return -1;
    }
    arr[front] = 0;
    front = (front + 1) % Capacity;
    Size_rn--; // not used here
    return 0;
}

int peek()
{
    if (isEmpty())
    {
        cout << "Queue is Empty" << '\n';
        return -1;
    }
    return arr[front];
}