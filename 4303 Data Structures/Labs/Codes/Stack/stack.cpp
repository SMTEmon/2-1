#include <bits/stdc++.h>

using namespace std;

struct Node
{
    char data;
    Node *next = nullptr;
};

Node *head = nullptr;

void addst(int val)
{
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = head;
    head = newNode;
    return;
}

void popst()
{
    if (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    return;
}

Node *topst()
{
    return head;
}

bool isEmpty()
{
    return head == nullptr;
}