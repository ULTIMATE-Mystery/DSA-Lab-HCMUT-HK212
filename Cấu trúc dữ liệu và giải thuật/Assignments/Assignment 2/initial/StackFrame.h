#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__
#include <string>
#include <stack>
/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize;  // max size of operand stack
    int localVarSpaceSize; // size of local variable space
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    class Stack {
        int index = -1;
        float* operandStack = new float[0];
        int size = 0;
    public:
        void adjustCapacity (int newSize) {
            float* temp = new float [newSize];
            for (int i = 0; i < size; i++) {
                temp[i] = operandStack[i];
            }
            delete[] operandStack;
            operandStack = temp;
        }
        bool isEmpty() {
            return index == -1;
        }
        bool isFull() {
            return index == 31;
        }
        void push (float dataValue, int dataType) {
            adjustCapacity (size += 2);
            operandStack [++index] = dataValue;
            operandStack [++index] = dataType;
        }
        void pop() {
            index -= 2;
            adjustCapacity (size -= 2);
        }
        float getDataValueAt (int index) {
            return operandStack [index];
        }
        int maxIndex() {
            return index;
        }
        float topDataValue() {
            return operandStack [index - 1];
        }
        int topDataType() {
            return operandStack [index];
        }
        int belowTopDataType() {
            return operandStack [index - 2];
        }
        void destroyStack () {
            delete[] operandStack;
        }
    };
    // AVL Tree
class AVL_Tree {
    struct AVL_Node {
        std::string key;
        float dataValue;
        int dataType;
        AVL_Node *parent;
        AVL_Node *left;
        AVL_Node *right;
        int height;
    };
    AVL_Node* root;

	int compareKey(std::string insertKey, std::string nodeKey) {
        if ((insertKey.compare(nodeKey)) > 0) {
            return 1;  
        }
        else if((insertKey.compare(nodeKey)) < 0) {
            return -1;  
        }
        else return 0;
    }

    int countNode (AVL_Node* root) {
        //base case
        if (root == NULL)
            return 0;

        //recursive call to left child and right child and
        // add the result of these with 1 ( 1 for counting the root)
        else {
            return 1 + countNode(root->left) + countNode(root->right);
        }
    }

    /*
    Function to get the height of the tree
*/
int height(AVL_Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

/*
    Function to create a new AVL_Node 
    Adding the newly created node as leaf node
*/

AVL_Node* newAVL_Node(AVL_Node* par, std::string key, float dataValue, int dataType) {
    AVL_Node* node = new AVL_Node();
    node->key = key;
    node->dataValue = dataValue;
    node->dataType = dataType;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->parent = par;
    return (node);
}

/*
    Function to update the heights
*/
void update_height(AVL_Node* root){
    if (root != NULL) {
        int val = 1;
        if (root->left != NULL)
            val = root->left->height + 1;
        if (root->right != NULL)
            val = std::max(
                val, root->right->height + 1);
        root->height = val;
    }
}

/*
    Function for right rotation
*/
AVL_Node *rightRotate(AVL_Node *y){
    AVL_Node *x = y->left;
    AVL_Node *T2 = x->right;

    if (x->right != NULL)
        x->right->parent = y;

/*
    Perform rotation
*/
    y->left = T2;
    x->right = y;

    x->parent = y->parent;
    y->parent = x;

    if (x->parent != NULL && y->key < x->parent->key) {
        x->parent->left = x;
    }
    else{
        if (x->parent != NULL)
            x->parent->right = x;
    }

    y = x;

/*
    Update the heights
*/    
    update_height(y->left);
    update_height(y->right);
    update_height(y);
    update_height(y->parent);

/*
    Return new root
*/
    return y;
}

/*
    Function for left rotation
*/
AVL_Node *leftRotate(AVL_Node *x){
    AVL_Node *y = x->right;
    AVL_Node *T2 = y->left;

/*
    Perform rotation
*/
    x->right = T2;

    if (y->left != NULL)
        y->left->parent = x;
    y->left = x;

    y->parent = x->parent;
    x->parent = y;

    if (y->parent != NULL && x->key < y->parent->key) {
        y->parent->left = y;
    }
    else{
        if (y->parent != NULL)
            y->parent->right = y;
    }

/*
    Update heights
*/

    update_height(x->left);
    update_height(x->right);
    update_height(x);
    update_height(x->parent);

/*
    Return new root
*/
    return y;
}

/*
    Function to find the Balance factor of Nodes
*/
int getBalance(AVL_Node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


/*
    Function to construct a tree.
*/
AVL_Node* AVL_insert(AVL_Node *par, AVL_Node* root, std::string key, float dataValue, int dataType){

/*
    Perform the normal BST insertion
*/
    if (root == NULL)
        return(newAVL_Node(par, key, dataValue, dataType));

    else if (compareKey(key, root->key) == -1)
        root->left = AVL_insert(root, root->left, key, dataValue, dataType);

    else if (compareKey(key, root->key) == 1)
        root->right = AVL_insert(root, root->right, key, dataValue, dataType);

    else if (compareKey(key, root->key) == 0) {
        root->dataValue = dataValue;
        root->dataType = dataType;
    }

    else 
        return root;

/*
    Step 1: Find the balance factor of parent\
*/
    int balance = getBalance(root);
/*
    If this Node becomes unbalanced, all four cases are:
*/
/*
    1. Left Left Case
*/
    if (balance > 1 && compareKey(key, root->left->key) == -1) 
        return rightRotate(root);

/*
    2. Right Right Case
*/
    if (balance < -1 && compareKey(key, root->right->key) == 1) 
        return leftRotate(root);

/*
    3. Left Right Case
*/
    if (balance > 1 && compareKey(key, root->left->key) == 1){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

/* 
    4. Right Left Case
*/
    if (balance < -1 && compareKey(key, root->right->key) == -1){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

/*
    Update the heights
*/
    update_height(root);

/*
    Return the (unchanged) Node pointer
*/
    return root;
}

/* 
    Search key
*/

AVL_Node* AVL_search_key(AVL_Node* root, std::string key) {
		if (root == nullptr || compareKey (key, root->key) == 0) {
			return root;
		}
		else if (compareKey (key, root->key) == -1) {
			return AVL_search_key(root->left, key);
		} 
		else if (compareKey (key, root->key) == 1) {
            return AVL_search_key(root->right, key);
        }
        else return NULL;
}

/*
    Find parent of a node
*/
AVL_Node* findParent(AVL_Node* root, std::string key) {
    if (AVL_search_key(root, key)->parent != NULL)
        return AVL_search_key(root, key)->parent;
    else
        return root->parent;
}

void destroyTree(AVL_Node*& root) {
  if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = NULL; 
}

public:
    AVL_Tree () {
        root = NULL;
    }
    void insert (std::string key, float dataValue, int dataType) {
        if (dataType == 0) {
            root = AVL_insert(NULL, root, key, (int)dataValue, dataType);
        }
        else {
            root = AVL_insert(NULL, root, key, (float)dataValue, dataType);
        }
    }
    int getSize () {
        return countNode (root);
    }
    AVL_Node* searchKey (std::string key) {
        return AVL_search_key(root, key);
    }
    AVL_Node* findParent (std::string key) {
        return findParent (root, key);
    }
    void destroyTree () {
        destroyTree (root);
    }
};
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run (std::string filename);
};
#endif // !__STACK_FRAME_H__