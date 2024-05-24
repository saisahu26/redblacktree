//Saikapish Sahu
//5/23/24
//RedBlack Tree
//Worked on Code with Arjun V and Nikaansh S

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

struct Node
{ // Thus is the node struct for the tree
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color; // One is red zero is black

    Node(int x) : data(x), parent(NULL), left(NULL), right(NULL), color(1) {} // sets color to red on construction
};

void enter(Node *&root);                        // asks for user input for numbers
void add(Node *&root, int newData);             // adds nodes to the tree folowing binary search tree rules
void fixer(Node *current, Node *&root);         // This funtion will fix the tree after new nodes are added
void fixerD(Node *current, Node *&root);        // this funtion will fix the tree after a node is removed
void transplant(Node *u, Node *v, Node *&root); // this funtion will transplant nodes in the tree. This will be used in the deletion funtion
void rRotate(Node *node, Node *&root);          // right rotation
void lRotate(Node *node, Node *&root);          // left rotation
void print(Node *root, int level);              // prints out the tree
void find(Node *root, int value);               // finds values in the tree
void addFile(Node *&root);                      // add numbrers from file
Node *findR(Node *root, int value);             // finds nodes
void remove(Node *current, Node *&root);        // removes nodes

int main()
{
    bool sR = true;
    char input[80];
    Node *root = NULL;

    while (sR == true)
    {
        cout << "Enter add, addfile, find, print, remove, or quit" << endl;
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
        if (strcmp(input, "remove") == 0)
        {
            cout << "Please enter the value you wish to remove " << endl;
            int findI = 0;
            cin >> findI;
            Node *current = findR(root, findI);
            remove(current, root);
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
        bool right = NULL;
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
    { // if it has a parent
        if (root->color == 1)
        { // if the node is red
            cout << 'V' << root->data << " R "
                 << "P" << root->parent->data << endl;
        }
        else
        { // if it is black
            cout << 'V' << root->data << " B "
                 << "P" << root->parent->data << endl;
        }
    }
    else
    { // if it does not have a parent
        if (root->color == 1)
        { // if it is red
            cout << 'V' << root->data << " R " << endl;
        }
        else
        { // if it is black
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

void transplant(Node *u, Node *v, Node *&root)
{ // This funtion
    if (u->parent == NULL)
    { // if root
        root = v;
    }
    else if (u == u->parent->left)
    { // if left child
        u->parent->left = v;
    }
    else
    { // if right child
        u->parent->right = v;
    }
    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

void remove(Node *current, Node *&root)
{ // removes nodes rom the tree and calls the fixerD to fix the tree as per Red Black standards
    int oc = current->color;
    Node *x;
    if (current->left == NULL)
    { // case 1 no left child
        x = current->right;
        transplant(current, current->right, root);
    }
    if (current->right == NULL)
    { // case 2 no right child
        x = current->left;
        transplant(current, current->left, root);
    }
    if (current->right != NULL && current->left != NULL)
    { // case 3 has both children
        Node *y = current->right;
        while (y->left != NULL)
        {
            y = y->left;
        } // find minumuim
        oc = y->color;
        x = y->right;
        if (x == NULL)
        {
            x = new Node(NULL);
            x->parent = y;
        }

        if (y->parent == current)
        {
            if (x != NULL)
            {
                x->parent = y;
            }
        }
        else
        {
            transplant(y, y->right, root);
            y->right = current->right;
            y->right->parent = y;
        }
        transplant(current, y, root);
        y->left = current->left;
        y->left->parent = y;
        y->color = current->color;
    }
    if (oc == 0)
    { // if the node being deleted is black
        if (x != NULL)
        {
            fixerD(x, root);
        }
        if (x == NULL)
        {
            x = new Node(NULL);
            x->parent = current->parent;
            x->color = 0;

            if (current->parent->left == current)
            {
                current->parent->left = x;
            }
            else if (current->parent->right == current)
            {
                current->parent->right = x;
            }
            fixerD(x, root);
        }
        delete current;
    }
}

void fixerD(Node *current, Node *&root)
{ // fixes the tree when a node is removed as to follow redblack requirments
    // print(root, 0);
    Node *s;
    while (current != root && current->color == 0)
    {
        if (current->parent->left == current)
        {
            s = current->parent->right;
            if (s->color == 1)
            { // case 1
                s->color = 0;
                current->parent->color = 1;
                lRotate(current->parent, root);
                current = current->parent->right;
            }
            if ((s == NULL || (s != NULL && s->color == 0)) &&
                (s->left == NULL || (s->left != NULL && s->left->color == 0)) &&
                (s->right == NULL || (s->right != NULL && s->right->color == 0)))
            { // case 2
                s->color = 1;
                current = current->parent;
            }
            else
            {
                if ((s == NULL || (s != NULL && s->color == 0)) &&
                    (s->left != NULL && (s->left->color == 1)) &&
                    (s->right == NULL || (s->right != NULL && s->right->color == 0)))
                { // case 3
                    s->left->color = 0;
                    s->color = 1;
                    rRotate(s, root);
                    s = current->parent->right;
                }
                s->color = current->parent->color;
                current->parent->color = 0;
                lRotate(current->parent, root);
                current = root;
            }
        }
        else
        { // if s is the left child
            s = current->parent->left;
            if (s->color == 1)
            { // case 1
                s->color = 0;
                current->parent->color = 1;
                rRotate(current->parent, root);
                current = current->parent->right;
            }
            if ((s == NULL || (s != NULL && s->color == 0)) &&
                (s->left == NULL || (s->left != NULL && s->left->color == 0)) &&
                (s->right == NULL || (s->right != NULL && s->right->color == 0)))
            { // case 2
                s->color = 1;
                current = current->parent;
            }
            else
            {
                if ((s == NULL || (s != NULL && s->color == 0)) &&
                    (s->left != NULL && (s->left->color == 1)) &&
                    (s->right == NULL || (s->right != NULL && s->right->color == 0)))
                { // case 3
                    s->left->color = 0;
                    s->color = 1;
                    lRotate(s, root);
                    s = current->parent->right;
                }
                s->color = current->parent->color;
                current->parent->color = 0;
                rRotate(current->parent, root);
                current = root;
            }
        }
    }
    current->color = 0;
}
