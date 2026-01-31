#include <bits/stdc++.h>

using namespace std;

class XORLL
{
public:
    struct Node
    {
        int value;
        Node *npx;

        Node(int val) : value(val), npx(nullptr) {}
    };

    static Node *head;

    void add(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head->npx = newNode;
            newNode->npx = head;
        }
        else
        {
        }
    }
};

int main()
{
    XORLL::head = nullptr;
}
