#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    int height;
    int cnt;
    int size;
    Node *left, *right;
    Node(int _data)
    {
        data = _data;
        height = 0;
        cnt = 1;
        size = 0;
        left = right = NULL;
    }
};

int getheight(Node *x)
{
    return x ? x->height : 0;
}

int getsize(Node *x)
{
    return x ? x->size : 0;
}

Node *rotateleft(Node *x)
{
    Node *w = x->left;
    x->left = w->right;
    w->right = x;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;
    w->height = max(getheight(w->left), x->height) + 1;
    x->size = x->cnt + getsize(x->left) + getsize(x->right);
    w->size = w->cnt + getsize(w->left) + x->size;
    return w;
}

Node *rotateright(Node *x)
{
    Node *w = x->right;
    x->right = w->left;
    w->left = x;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;
    w->height = max(x->height, getheight(w->right)) + 1;
    x->size = x->cnt + getsize(x->left) + getsize(x->right);
    w->size = w->cnt + getsize(w->left) + x->size;
    return w;
}

Node *rotateleftright(Node *z)
{
    z->right = rotateleft(z->right);
    return rotateright(z);
}

Node *rotaterightleft(Node *z)
{
    z->left = rotateright(z->left);
    return rotateleft(z);
}

bool search(Node *&root, int data)
{
    if (!root)
    {
        return false;
    }
    if (root->data == data)
    {
        return true;
    }
    if (root->data > data && search(root->left, data))
    {
        if (root->left->data == data)
        {
            root = rotateleft(root);
        }
        else if (root->left->data < data)
        {
            root = rotaterightleft(root);
        }
        return true;
    }
    else if (root->data < data && search(root->right, data))
    {
        if (root->right->data == data)
        {
            root = rotateright(root);
        }
        else if (root->right->data > data)
        {
            root = rotateleftright(root);
        }
        return true;
    }
    return false;
}

Node *insert(Node *root, int data)
{
    if (!root)
    {
        root = new Node(data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
        if (root->right->data == data)
        {
            root = rotateright(root);
        }
        else if (root->right->data > data)
        {
            //node is in the left subtree of root->right
            root = rotateleftright(root);
        }
    }
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
        if (root->left->data == data)
        {
            root = rotateleft(root);
        }
        else if (root->left->data < data)
        {
            //data is in the right subtree of left child of root
            //do right left rotation
            root = rotaterightleft(root);
        }
    }

    root->size = getsize(root->left) + getsize(root->right) + root->cnt;
    root->height = max(getheight(root->left), getheight(root->right)) + 1;
    return root;
}

void inorder(Node *root)
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
    cout << "\n";
}
void levelorder(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (!temp)
        {
            if (!q.empty())
                q.push(NULL);

            cout << "\n";
            continue;
        }
        cout << temp->data << " ";
        if (temp->left)
        {
            q.push(temp->left);
        }
        if (temp->right)
        {
            q.push(temp->right);
        }
    }
}

int main()
{
    srand(time(NULL));
    Node *root = NULL;
    for (int i = 13; i >= 1; i--)
        root = insert(root, rand() % 13 + 1);
    inorder(root);
    cout << "Search : " << 12 << "\n";
    if (search(root, 12))
        levelorder(root);
    cout << "Search : " << 4 << "\n";
    if (search(root, 4))
        levelorder(root);
    return 0;
}