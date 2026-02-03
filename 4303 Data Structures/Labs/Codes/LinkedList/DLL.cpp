#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data = 0;
    Node *next = nullptr;
    Node *prev = nullptr;
};

Node *head = nullptr;

void insertAtHead(int val)
{
    Node *newNode = new Node();
    newNode->data = val;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }
}

void insertAtTail(int val)
{
    Node *cur = head;
    Node *newNode = new Node();
    newNode->data = val;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    cur->next = newNode;
    newNode->prev = cur;
}

void insertAfter(int refval, int val)
{
    Node *cur = head;
    bool found = false;
    while (cur->next != nullptr && !found)
    {
        if (cur->data == refval)
        {
            found = true;
            break;
        }
        cur = cur->next;
    }

    if (found)
    {
        Node *newNode = new Node();
        newNode->data = val;
        newNode->prev = cur;
        newNode->next = cur->next;
        newNode->next->prev = newNode;
        cur->next = newNode;
    }
    else
    {
        cout << "Not found, adding to tail." << "\n";
        insertAtTail(val);
    }
}

void displayForward()
{
    Node *cur = head;
    while (cur->next != nullptr)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << cur->data << "\n";
}

void displayBackward()
{
    Node *cur = head;
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    while (cur != head)
    {
        cout << cur->data << " ";
        cur = cur->prev;
    }
    cout << cur->data << "\n";
}

bool search(int key)
{
    Node *cur = head;

    bool found = false;
    while (!found)
    {
        if (cur->data == key)
        {
            found = true;
            break;
        }
        if (cur->next == nullptr)
            break;

        cur = cur->next;
    }

    return found;
}

void deleteVal(int val)
{
    Node *cur = head;

    bool found = false;
    while (cur->next != nullptr && !found)
    {
        if (cur->next->data == val)
        {
            found = true;
        }
        cur = cur->next;
    }

    if (found)
    {
        cur->next = cur->next->next;
        cur->next->prev = cur;
        free(cur);
    }
    else
        cout << "Not found" << "\n";
}

int main()
{
    insertAtHead(10);
    insertAtHead(5);
    insertAtTail(20);
    insertAtTail(30);
    insertAtTail(40);
    insertAfter(1, 15);
    cout << search(15) << "\n";

    // displayForward();
    // displayBackward();
}