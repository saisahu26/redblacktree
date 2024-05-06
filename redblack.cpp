//saikapish sahu
//red black tree
//4/28/24
//code worked on with Arjun V and Nikaansh S
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color; // One is red zero is black

    Node(int x) : data(x), parent(NULL), left(NULL), right(NULL), color(1) {} // sets color to red on construction
};

void enter(Node *&root);                         // asks for user input for numbers
void add(Node *&root, int newData);              // adds nodes to the tree folowing binary search tree rules
void fixer(Node *current, Node *&root);          // This funtion will fix the tree after new nodes are added
void rRotate(Node *node, Node *&root);           // right rotation
void lRotate(Node *node, Node *&root);           // left rotation
void print(Node *root, int level);               // prints out the tree
void find(Node *root, int value);                // finds values in the tree
void addFile(Node *&root);                       // add numbrers from file
Node *findR(Node *root, int value);              // finds nodes
void remove(Node *n, Node *parent, Node *&root); // removes nodes

int main()
{
    bool sR = true;
    char input[80];
    Node *root = NULL;

    while (sR == true)
    {
        cout << "Enter add, addfile, find, or quit" << endl;
        cin >> input;
        if (strcmp(input, "add") == 0)
        {
            enter(root);
        }
        if (strcmp(input, "find") == 0)
        {
            int value = 0;
            cout << "please enter in a number" << endl;
            cin >> value;
            find(root, value);
        }
        if (strcmp(input, "addfile") == 0)
        {
            addFile(root);
        }
        if (strcmp(input, "print") == 0)
        {
            print(root, 0);
        }
        if (strcmp(input, "quit") == 0)
        {
            sR = false;
        }
    }
    return 0;
}

void enter(Node *&root)
{ // will ask for user input and add this to the tree
    int input = 0;
    cout << "enter a number" << endl;
    cin >> input;
    add(root, input);
}

void addFile(Node *&root)
{ // Will add ints from a file
    cout << "enter file name(and .txt) " << endl;
    char input[20];
    cin >> input;
    ifstream fin(input);
    int temp;
    while (fin >> temp)
    {
        add(root, temp);
    }
    fin.close();
}

void add(Node *&root, int newData)
{ // adds the values to the tree
    if (root == NULL)
    { // when there is nothing in the tree
        root = new Node(newData);
        root->color = 0;
        return;
    }
    else
    { // if the root is not null
        Node *current = root;
        Node *parent = NULL;
        bool right = false;
        while (current != NULL)
        { // iterate down the left or right sub trees
            parent = current;
            if (current->data > newData)
            { // left subtree
                current = current->left;
                right = false;
            }
            else if (current->data < newData)
            { // right subtree
                current = current->right;
                right = true;
            }
        }
        if (right == true)
        { // set new right node
            parent->right = (new Node(newData));
            current = parent->right;
            current->parent = parent;
        }
        else if (right == false)
        { // set new left node
            parent->left = (new Node(newData));
            current = parent->left;
            current->parent = (parent);
        }
        fixer(current, root);
    }
}

void fixer(Node *current, Node *&root)
{ // responsible for fixing the tree after the add funtion
    while (current != root && current->parent->color == 1)
    { // while parent is red

        if (current->parent == current->parent->parent->right)
        { // if uncle is the left child
            Node *uncle = current->parent->parent->left;
            if (uncle != NULL && uncle->color == 1)
            { // if parent is red and uncle is red

                current->parent->color = 0;
                uncle->color = 0;
                current->parent->parent->color = 1;
                current = current->parent->parent;
            }

            else if (uncle == NULL || (uncle != NULL && uncle->color == 0))
            { // parent is red and u is black
                if (current->parent->left == current)
                { // current is a left child
                    current = current->parent;
                    rRotate(current, root);
                }

                current->parent->color = 0;
                current->parent->parent->color = 1;
                lRotate(current->parent->parent, root);
            }
        }
        else
        { // if uncle is right child
            Node *uncle = current->parent->parent->right;

            if (uncle != NULL && uncle->color == 1)
            { // if parent is red and uncle is red
                current->parent->color = 0;
                uncle->color = 0;
                current->parent->parent->color = 1;
                current = current->parent->parent;
            }

            else if (uncle == NULL || (uncle != NULL && uncle->color == 0))
            { // parent is red and u is black

                if (current->parent->right == current)
                { // if parent is right child
                    current = current->parent;
                    lRotate(current, root);
                }

                current->parent->color = 0;
                current->parent->parent->color = 1;
                rRotate(current->parent->parent, root);
            }
        }
        if (current == root)
        { // if the new thing to be changed is the root just set it too black
            current->color = 0;
        }
    }
}

void print(Node *root, int level)
{ // will print the tree
    if (!root)
    { // if nothing in tree or nothing left to print
        return;
    }
    print(root->right, level + 1); // prints out the left subtree

    for (int i = 0; i < level; i++)
    {
        cout << "\t";
    }
    if (root->parent != NULL)
    {
        if (root->color == 1)
        {
            cout << 'V' << root->data << " R "
                 << "P" << root->parent->data << endl;
        }
        else
        {
            cout << 'V' << root->data << " B "
                 << "P" << root->parent->data << endl;
        }
    }
    else
    {
        if (root->color == 1)
        {
            cout << 'V' << root->data << " R " << endl;
        }
        else
        {
            cout << 'V' << root->data << " B " << endl;
        }
    }
    print(root->left, level + 1); // prints the left subtree
}

void lRotate(Node *node, Node *&root)
{ // left rotation
    Node *x = node->right;
    node->right = x->left;
    if (x->left != NULL)
    {
        x->left->parent = node;
    }
    x->parent = node->parent;

    if (node->parent == NULL)
    {
        root = x;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = x;
    }
    else
    {
        node->parent->right = x;
    }

    x->left = node;
    node->parent = x;
}

void rRotate(Node *node, Node *&root)
{ // right rotation
    Node *x = node->left;
    node->left = x->right;
    if (x->right != NULL)
    { // rights child is not NULL
        x->right->parent = node;
    }
    x->parent = node->parent;

    if (node->parent == NULL)
    {
        root = x;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = x;
    }
    else
    {
        node->parent->left = x;
    }

    x->right = node;
    node->parent = x;
}

void find(Node *root, int value)
{ // will find values
    if (!root)
    {
        return;
    }

    if (root->data == value)
    {
        cout << "The given value is in the tree" << endl;
        return;
    }

    if (root->data > value)
    {
        find(root->left, value); // searches the left subtree
    }
    else
    {
        find(root->right, value); // searches the right subtree
    }
}

void remove(Node *n, Node *parent, Node *&root)
{ // will remove a node
    if (n == NULL)
    { // if n is null
        return;
    }

    if (n->left == NULL && n->right == NULL)
    { // no children
        if (parent != NULL)
        { // if there is a parent
            if (parent->left == n)
            {                        // if n is left
                parent->left = NULL; // set parent left to null
            }
            else
            {
                parent->right = NULL; // sets right to null
            }
        }
        else
        {
            root = NULL; // If root is being removed
        }
        delete n;
        return;
    }

    if ((n->left == NULL) != (n->right == NULL))
    { // one child
        Node *child;
        if (n->left != NULL)
        { // if left child exists
            child = n->left;
        }
        else
        { // if right child exists
            child = n->right;
        }
        if (parent != NULL)
        { // if there is a parent
            if (parent->left == n)
            { // if parents lchild is n
                parent->left = child;
            }
            else
            { // if rchild is n
                parent->right = child;
            }
        }
        else
        { // if the root needs to be removed
            root = child;
        }
        delete n;
        return;
    }
    else
    {                       // for two child
        Node *s = n->right; // sets s to the r child of n
        Node *sP = NULL;    // sets s parent to NULL
        while (s->left != NULL)
        {                // while s does not have a l child
            sP = s;      // s aprent = s
            s = s->left; // s = s lchild
        }

        if (sP != NULL)
        {                        // if s parent exists
            sP->left = s->right; // parent's left is s's right
        }
        else                     // if it dosent exist
            n->right = s->right; // n's right is s's right

        n->data = s->data; // set the value of n to the value of s
        delete s;          // delete s
    }
}

Node *findR(Node *root, int value)
{ // find the node
    if (root == nullptr || root->data == value)
    {
        return root;
    }

    Node *leftResult = findR(root->left, value);
    if (leftResult != nullptr)
    {
        return leftResult;
    }

    return findR(root->right, value);
}
