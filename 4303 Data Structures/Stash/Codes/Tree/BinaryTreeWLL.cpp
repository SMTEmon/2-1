#include <bits/stdc++.h>

class Node
{

private:
    int val;
    Node *leftNode;
    Node *rightNode;

public:
    static Node *root;
    Node() : val(0), leftNode(nullptr), rightNode(nullptr) {}
    Node(int val) : val(val), leftNode(nullptr), rightNode(nullptr) {}

    static Node *insertNode(Node *currentNode, int val)
    {
        if (currentNode == nullptr)
        {
            return new Node(val);
        }
        else if (val < currentNode->val)
        {
            currentNode->leftNode = insertNode(currentNode->leftNode, val);
        }
        else
        {
            currentNode->rightNode = insertNode(currentNode->rightNode, val);
        }
        return currentNode;
    }

    static void traverse(const Node *currentNode)
    { // traversing left to right
        if (currentNode == nullptr)
            return;
        traverse(currentNode->leftNode);
        std::cout << currentNode->val << " ";
        traverse(currentNode->rightNode);
    }

    static Node *search(Node *currentNode, int val)
    {
        if (currentNode == nullptr)
            return nullptr;

        if (currentNode->val == val)
        {
            std::cout << "Found" << std::endl;
            return currentNode;
        }

        if (val < currentNode->val)
        {
            search(currentNode->leftNode, val);
        }
        else
        {
            search(currentNode->rightNode, val);
        }
        return nullptr;
    }

    static int getDepth(Node *currentNode)
    {
        if (currentNode == nullptr)
            return 0;

        int leftDepth = getDepth(currentNode->leftNode);
        int rightDepth = getDepth(currentNode->rightNode);
        return 1 + std::max(leftDepth, rightDepth);
    }

    static void levelTraverse(Node *currentNode)
    {
        if (currentNode == nullptr)
            return;

        std::queue<Node *> q;
        q.push(currentNode);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            std::cout << current->val << " ";

            if (current->leftNode != nullptr)
                q.push(current->leftNode);
            if (current->rightNode != nullptr)
                q.push(current->rightNode);
        }
    }

    static Node* findLargest(Node* root){
        if (root->rightNode == nullptr) return root;

        return findLargest(root->rightNode);
    }

    static Node* findSmallest(Node* root){
        if (root->leftNode == nullptr) return root;

        return findSmallest(Node->leftNode);
    }



    static Node* deleteTree(Node *root, int value){
        if (root == nullptr) return root;
        if (root->val < value) {
            root->leftNode = deleteTree(root->leftNode , value);
        }
        else if (root->val > value){
            root->rightNode = deleteTree(root->rightNode, value);
        }
        else{
            if (root->leftNode && root->rightNode){
                Node *temp = findSmallest(root -> rightNode);
                root->val = temp->val;
                delete temp;
            }
            else{
                Node *temp = root;
                if (root->leftNode) root = root->leftNode;
                else if (root->rightNode) root = root->rightNode; 
                delete temp;
            }
        }
        return root;

    }
};

Node *Node::root = nullptr;

int main()
{
    Node::root = Node::insertNode(Node::root, 10);
    Node::insertNode(Node::root, 20);
    Node::insertNode(Node::root, 22);
    Node::insertNode(Node::root, 30);
    Node::insertNode(Node::root, 32);
    Node::insertNode(Node::root, 12);
    Node::insertNode(Node::root, 11);
    Node::insertNode(Node::root, 33);
    Node::traverse(Node::root);

    std::cout << std::endl;

    if (Node::search(Node::root, 23) == nullptr)
        std::cout << "Not Found!" << std::endl;

    std::cout << Node::getDepth(Node::root) << std::endl;

    Node::levelTraverse(Node::root);
}