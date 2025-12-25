#include <bits/stdc++.h>
using namespace std;

class ArrayBinaryTree {
private:
    vector<int> tree;
    int capacity;
    
public:
    ArrayBinaryTree(int size) {
        capacity = size;
        tree.resize(size, -1); // empty node
    }
    
    void insert(int value, int index) {
        if (index >= capacity) {
            cout << "Index out of bounds!" << endl;
            return;
        }
        tree[index] = value;
    }
    
    void insertRoot(int value) {
        insert(value, 0);
    }
    
    void insertLeftChild(int parentIndex, int value) {
        insert(value, 2 * parentIndex + 1);
    }
    
    void insertRightChild(int parentIndex, int value) {
        insert(value, 2 * parentIndex + 2);
    }
    
    int getLeftChild(int parentIndex) {
        int leftIndex = 2 * parentIndex + 1;
        return (leftIndex < capacity) ? tree[leftIndex] : -1;
    }
    
    int getRightChild(int parentIndex) {
        int rightIndex = 2 * parentIndex + 2;
        return (rightIndex < capacity) ? tree[rightIndex] : -1;
    }
    
    int getParent(int childIndex) {
        if (childIndex == 0) return -1;
        return tree[(childIndex - 1) / 2];
    }
    
    void printTree() {
        cout << "Array Representation: ";
        for (int val : tree) {
            if (val != -1) cout << val << " ";
            else cout << "- ";
        }
        cout << endl;
    }
};


void demoArrayTree() {
    ArrayBinaryTree tree(15);
    
    tree.insertRoot(1);
    tree.insertLeftChild(0, 2);
    tree.insertRightChild(0, 3);
    tree.insertLeftChild(1, 4);
    tree.insertRightChild(1, 5);
    
    tree.printTree();
    cout << "Left child of 0: " << tree.getLeftChild(0) << endl;
    cout << "Right child of 0: " << tree.getRightChild(0) << endl;
}