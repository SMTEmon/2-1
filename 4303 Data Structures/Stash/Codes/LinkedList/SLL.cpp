#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node *next = nullptr;
};

Node *head = nullptr;

void insertAtHead(int val)
{
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = head;
    head = newNode;
}

void insertAtTail(int val)
{
    if (head == nullptr)
    {
        insertAtHead(val);
        return;
    }
    Node *cur = head;
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    Node *newNode = new Node();
    newNode->data = val;
    cur->next = newNode;
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
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = cur->next;
    cur->next = newNode;
}

void display()
{
    Node *cur = head;
    while (cur->next != nullptr)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << cur->data;
    cout << "\n";
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

void update(int oldVal, int newVal)
{
    Node *cur = head;

    bool found = false;
    while (cur->next != nullptr && !found)
    {

        if (cur->data == oldVal)
        {
            found = true;
            break;
        }
        cur = cur->next;
    }

    if (found)
        cur->data = newVal;
    else
        cout << "Not found" << "\n";
}

void deleteVal(int val)
{
    Node *cur = head;

    if (cur->data == val)
    {
        head = head->next;
        free(cur);
        return;
    }

    bool found = false;
    while (cur->next != nullptr && !found)
    {
        if (cur->next->data == val)
        {
            found = true;
            break;
        }
        cur = cur->next;
    }

    if (found)
    {
        Node *temp = cur->next;
        cur->next = cur->next->next;
        free(temp);
    }
    else
        cout << "Not found" << "\n";
}

int main()
{
    insertAtTail(10);
    insertAtTail(20);
    insertAtTail(30);
    deleteVal(40);
    cout << search(30);

    display();
    return 0;
}