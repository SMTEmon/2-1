#include<bits/stdc++.h>

using namespace std;

class Node{

public:
    int key;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), height(0){}
    Node(int k, Node * p) : key(k), left(nullptr), right(nullptr), parent(p), height(0){}
    Node(int k, Node * p, int h) : key(k), left(nullptr), right(nullptr), parent(p), height(h){}

};

class BST{

public:

    Node* root = nullptr;

    BST() : root(nullptr) {}

    Node* insert(int val){
        Node* newNode = new Node(val);
        
        if (root == nullptr) {
            root = newNode;
            newNode->height = 0;
            return newNode;
        }
            Node* pre_temp = root;
            Node* temp = root;
            while(true){
                newNode->height++;
                newNode->parent = pre_temp;

                if (temp->key > val){
                    if (temp->left)temp = temp->left;
                    else{
                        temp->left = newNode;
                        return newNode;
                    }
                }
                else {
                    if (temp->right)temp = temp->right;
                    else{
                        temp->right = newNode; 
                        return newNode;
                    }
                }
                pre_temp = temp;
            }

    }

    void print_tree(Node* rootNow){
        if (rootNow == nullptr) return;
        print_tree(rootNow->left);
        cout << rootNow->key << " ";
        print_tree(rootNow->right);
        
    }

    Node* searchRec(Node* rootNow, int val){
        if (rootNow == nullptr || rootNow->key == val)  return rootNow;
        if (rootNow->key > val)
            return searchRec(rootNow->left, val);
        
        return searchRec(rootNow->right, val);

    }

    Node* search(Node* rootNow, int val){
        return searchRec(rootNow, val);
    }


    int get_height(int val){
        Node* node = search(root, val);
        return node->height;
    }

    void before_after(int value){
        Node* node = search(root, value);
        if (node->parent)cout << "Parent: " << node->parent->key << "\n";
        if (node->left) cout << "Left: " << node->left->key << "\n";
        if (node->right) cout << "Right: " << node->right->key << "\n";
    }


    void max_min(Node* rootNow, int value){
        Node* min = rootNow;
        Node* max = rootNow;

        while (min->left) min = min->left;
        while (max->right && max->key < value) max = max->right;

        cout << "MAX: " << max->key << " " << "MIN: " << min->key << "\n";
    }

    Node* findMin(Node* rootNow){
        Node* temp = rootNow;
        while (temp->left){
            temp = temp->left;
        }
        return temp;
    }


    void decHeight(Node* rootNow){
        if (rootNow == nullptr) return;
        decHeight(rootNow->left);
        rootNow->height--;
        decHeight(rootNow->right);
    }

    Node* deleteNode(Node* rootNow, int value){
        if (rootNow == nullptr) return rootNow;
        if (rootNow->key > value) rootNow->left = deleteNode(rootNow->left, value);
        else if (rootNow->key < value) rootNow->right = deleteNode(rootNow->right, value);
        else{
            if (rootNow->left == nullptr && rootNow->right == nullptr){
                delete rootNow;
                return nullptr;
            }
            else if (rootNow->left == nullptr){
                Node* temp = rootNow;
                delete rootNow;
                temp->parent->right = temp->right;
                temp->right->parent = temp->parent;
                decHeight(temp);
                return temp;
            }
            else if (rootNow->right == nullptr){
                Node* temp = rootNow;
                delete rootNow;
                temp->parent->left = temp->left;
                temp->left->parent = temp->parent;
                decHeight(temp);
                return temp;
            }
            else{
                Node* temp = findMin(rootNow);
                rootNow->key = temp->key;
                temp->parent->left = nullptr;
                delete temp;
                return rootNow;
            }

        } 
        return rootNow;
    }

    int find_lca(int val1, int val2){
        Node* node1 = search(root, val1);
        Node* node2 = search(root, val2);

        if (node1 == root || node2 == root){
            return -1;
        }

        while ((node1->height != node2 ->height)
        && (node1->parent != node2->parent)){
            if (node1->height > node2->height){
                if (node1->parent == nullptr) break;
                node1 = node1->parent;
            }
            else if (node1->height < node2->height){
                if (node2->parent == nullptr) break;
                node2 = node2->parent;
            }
            else {
                if (node1->parent == nullptr && node2->parent == nullptr){
                    break;
                }
                node1 = node1->parent;
                node2 = node2->parent;
            }
        }

        if (node1->parent == node2->parent) return node1->parent->key;
        else return -1;
    }

};


int main(){
    int a, b;
    bool exit = false;
    BST bst = BST();

    while (!exit){
        cin >> a;
        if (a == 9) {
            exit = !exit;
            continue;
        }

        if (a == 1){
            cin >> b;
            bst.insert(b);
            bst.print_tree(bst.root);
        }

        if (a == 2)
            bst.print_tree(bst.root);

        if (a == 3){
            cin >> b;
            Node* temp = bst.search(bst.root, b);
            if (temp) cout << "Found" << "\n";
            else cout << "Not Found" << "\n";
        }
        if(a == 4){
            cin >> b;
            cout << bst.get_height(b) << '\n';
        }
        if(a == 5){
            cin >> b;
            bst.before_after(b);
        }  
        if(a == 6){
            cin >> b;
            bst.max_min(bst.root, b);
        }
        if(a == 7){
            cin >> b;
            bst.deleteNode(bst.root, b);
        }
        if (a == 8){
            int c;
            cin >> b >> c;
            cout << bst.find_lca(b, c);
        }
    }
}
