#include <iostream>
using namespace std;

class node{
    friend class BST;
    private:
        int data;
        node* left;
        node* right;
        int height;
    public:
        node(int d);
        ~node();
};

node::node(int d){
    data = d;
    left = NULL;
    right = NULL;
    height = 0;
}

node::~node(){
    delete left;
    delete right;
}
    

class BST{
    private:
        node* root;
    public:
        BST();
        ~BST();
        void makeEmpty(node* t);
        node* insert(int x, node* t);
        node* singleRightRotate(node* &t);
        node* singleLeftRotate(node* &t);
        node* doubleLeftRotate(node* &t);
        node* doubleRightRotate(node* &t);
        node* findMin(node* t);
        node* findMax(node* t);
        node* remove(int x, node* t);
        int height(node* t);
        int getBalance(node* t);
        void inorder(node* t);

        void insert(int x);
        void display();
};
BST::BST(){
    root = NULL;
}
BST::~BST(){
    delete root;
}

void BST:: insert(int x){
    root = insert(x, root);
}

void BST:: display(){
    inorder(root);
    cout << endl;
}


void BST:: makeEmpty(node* t){
    if(t == NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

node* BST:: insert(int x, node* t){
    if(t == NULL){
        t = new node(x);
        t->data = x;
        t->height = 0;
        t->left = t->right = NULL;
    } else if(x < t->data){
        t->left = insert(x, t->left);
        if(height(t->left) - height(t->right) == 2){
            if(x < t->left->data)
                t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
        }
    } else if(x > t->data){
        t->right = insert(x, t->right);
        if(height(t->right) - height(t->left) == 2){
            if(x > t->right->data)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
            }
        }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

node* BST:: singleRightRotate(node* &t){
    node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

node* BST:: singleLeftRotate(node* &t){
    node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

node* BST:: doubleLeftRotate(node* &t){
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

node* BST:: doubleRightRotate(node* &t){
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

node* BST:: findMin(node* t){
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

node* BST:: findMax(node* t){
    if(t == NULL)
        return NULL;
    else if(t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

node* BST:: remove(int x, node* t){
     node* temp;
        // Element not found
        if(t == NULL)
            return NULL;

        // Searching for element
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right){
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2){
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2){
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
}

int BST:: height(node* t){
    return (t == NULL ? -1 : t->height);
}

int BST:: getBalance(node* t){
    if(t == NULL)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void BST:: inorder(node* t){
    if(t == NULL)
        return;
    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}


int main()
{
    BST t;
    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);
    t.insert(5);
    t.insert(35);
    t.insert(67);
    t.insert(43);
    t.insert(21);
    t.insert(10);
    t.insert(89);
    t.insert(38);
    t.insert(69);
    t.display();
}
