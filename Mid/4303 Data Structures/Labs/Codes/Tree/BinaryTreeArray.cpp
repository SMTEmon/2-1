#include <bits/stdc++.h>

using namespace std;

class BT
{
private:
    vector<int> vec;
    int sizee;

public:
    BT(int capacity)
    {
        sizee = capacity;
        vec.resize(sizee, -1);
    }
    void insert(int val, int index)
    {
        if (index >= sizee)
        {
            cout << "Index out of bounds!" << endl;
            return;
        }
        vec[index] = val;
    }

    void insertRoot(int value)
    {
        insert(value, 0);
    }

    void insertLeftChild(int parentIndex, int value)
    {
        insert(value, 2 * parentIndex + 1);
    }

    void insertRightChild(int parentIndex, int value)
    {
        insert(value, 2 * parentIndex + 2);
    }

    void insertIntoTreeLikeLL(int index, int val)
    {
        if (index >= sizee)
            return;
        if (vec[index] == -1)
        {
            insert(val, index);
            return;
        }
        else if (val < vec[index])
        {
            insertIntoTreeLikeLL(2 * index + 1, val);
        }
        else
        {
            insertIntoTreeLikeLL(2 * index + 2, val);
        }
    }

    int getLeftChild(int parentIndex)
    {
        int leftIndex = 2 * parentIndex + 1;
        return (leftIndex < sizee) ? vec[leftIndex] : -1;
    }

    int getRightChild(int parentIndex)
    {
        int rightIndex = 2 * parentIndex + 2;
        return (rightIndex < sizee) ? vec[rightIndex] : -1;
    }

    int getParent(int childIndex)
    {
        if (childIndex == 0)
            return -1;
        return vec[(childIndex - 1) / 2];
    }

    void levelTraverse()
    {
        cout << "Array Representation: ";
        for (int val : vec)
        {
            if (val != -1)
                cout << val << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }

    void inOrderTraverse(int index)
    {
        if (index >= sizee || vec[index] == -1)
            return;

        inOrderTraverse(2 * index + 1);
        cout << vec[index] << " ";
        inOrderTraverse(2 * index + 2);
    }
};

int main()
{

    BT tree(15);

    cout << "--- Inserting Elements using BST Logic ---" << endl;

    tree.insertIntoTreeLikeLL(0, 10);
    tree.insertIntoTreeLikeLL(0, 5);
    tree.insertIntoTreeLikeLL(0, 20);
    tree.insertIntoTreeLikeLL(0, 3);
    tree.insertIntoTreeLikeLL(0, 7);

    tree.levelTraverse();

    cout << "In-Order Traversal: ";
    tree.inOrderTraverse(0);
    cout << endl;
}