#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node *next = nullptr;
};

Node *head = nullptr;

void insertAtTail(int val)
{

    Node *newNode = new Node();

    if (head == nullptr)
    {
        head = newNode;
        head->data = val;
        head->next = head;
        return;
    }

    Node *cur = head;
    while (cur->next != head)
    {
        cur = cur->next;
    }

    newNode->data = val;
    newNode->next = head;
    cur->next = newNode;
}

void insertAfter(int refval, int val)
{
    Node *cur = head;
    bool found = false;
    while (cur->next != head && !found)
    {
        if (cur->data == refval)
        {
            found = true;
            break;
        }
        cur = cur->next;
    }

    if (cur->data == refval)
        found = true;

    if (!found)
    {
        cout << "Not found! Inserting at Tail." << "\n";
    }

    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = cur->next;
    cur->next = newNode;
}

void display()
{
    Node *cur = head;
    while (cur->next != head)
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
        if (cur->next == head)
            break;

        cur = cur->next;
    }

    return found;
}

void update(int oldVal, int newVal)
{
    Node *cur = head;

    bool found = false;
    while (!found)
    {
        if (cur->data == oldVal)
        {
            found = true;
            break;
        }
        if (cur->next == head)
            break;

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

    if (cur == head && cur->data == val)
    {
        Node *temp = head->next;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = cur->next;
        head = head->next;
        free(cur);
        return;
    }

    bool found = false;
    while (cur->next != head && !found)
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
    insertAtTail(20);
    insertAtTail(25);
    insertAtTail(30);
    insertAtTail(40);
    // update(20, 22);
    deleteVal(40);

    display();
}