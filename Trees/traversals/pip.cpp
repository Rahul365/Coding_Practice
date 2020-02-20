#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    Node(int data)
    {
        this->data = data;
        left = right = NULL;
    }
};
//Node - L - R
void preorder(Node *root)
{
    if (!root)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
//L - Node - R
void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
//L - R - Node
void postorder(Node *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void preorderIterative(Node *root)
{
    if (!root)
        return;
    stack<Node *> stk;
    while (true)
    {
        while (root)
        {
            cout << root->data << " ";
            stk.push(root);
            root = root->left;
        }
        if (stk.empty())
            break;
        root = stk.top();
        stk.pop();
        root = root->right;
    }
}

void inorderIterative(Node *root)
{
    if (!root)
        return;
    stack<Node *> stk;
    while (true)
    {
        while (root)
        {
            stk.push(root);
            root = root->left;
        }
        if (stk.empty())
            break;
        root = stk.top();
        stk.pop();
        cout << root->data << " ";
        root = root->right;
    }
}

void postorderIterative(Node *root)
{
    if (!root)
        return;
    Node *previous = NULL; //this pointer will tell us whether we are just coming from the left substree or right
    stack<Node *> stk;
    do
    {
        while (root)
        {
            stk.push(root);
            root = root->left;
        }
        while (!root && !stk.empty())
        {
            root = stk.top();
            if (!root->right || root->right == previous)
            {
                stk.pop();
                cout << root->data << " ";
                previous = root;
                root = NULL;
            }
            else
            {
                root = root->right;
            }
        }
    } while (!stk.empty());
}

/**
 * Boundary Traversal
*/
void printleaves(Node *root)
{
    if (!root)
        return;
    printleaves(root->left);
    if (!root->left && !root->right)
        cout << root->data << " ";
    printleaves(root->right);
}
//except leaf node print the left boundary in top down manner
void printleftboundary(Node *root)
{
    if (!root)
        return;
    if (root->left)
    {
        //to ensure top-down order print node's data first
        cout << root->data << " ";
        printleftboundary(root->left);
    }
    else if (root->right)
    {
        cout << root->data << " ";
        printleftboundary(root->right);
    }
}

//except leaf node print right boundary in bottom up manner
void printrightboundary(Node *root)
{
    if (!root)
        return;

    if (root->right)
    {
        printrightboundary(root->right);
        cout << root->data << " ";
    }
    else if (root->left)
    {
        printrightboundary(root->left);
        cout << root->data << " ";
    }
}

void printBoundary(Node *root)
{
    if (!root)
        return;

    cout << root->data << " ";

    printleftboundary(root->left);
    printleaves(root->left);
    printleaves(root->right);
    printrightboundary(root->right);
}
//------------------------------------
int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    /**
     *              1
     *             / \
     *            2   3
     *           /\   /\
     *          4  5 6  NULL
    */
    cout << "preorder : \n";
    cout << "rec : ";
    preorder(root);
    cout << "\n";
    cout << "itr : ";
    preorderIterative(root);
    cout << "\n";

    cout << "Inorder : \n";
    cout << "rec : ";
    inorder(root);
    cout << "\n";
    cout << "itr : ";
    inorderIterative(root);
    cout << "\n";

    cout << "Postorder : \n";
    cout << "rec : ";
    postorder(root);
    cout << "\n";
    cout << "itr : ";
    postorderIterative(root);
    cout << "\n";
    return 0;
}