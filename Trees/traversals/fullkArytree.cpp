#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node **child;
    Node(int _data, int k)
    {
        data = _data;
        child = new Node *[k];
        for (int i = 0; i < k; i++)
            child[i] = NULL;
    }
};

Node *buildtree(int *preorder, int i, int n, int k)
{
    if (i >= n)
        return NULL;

    Node *root = new Node(preorder[i], k);
    for (int childnode = k * i + 1; childnode <= (k * i + k); childnode++)
    {
        //modulo is not used here to avoid miscalculation when i = 0
        //then chidrens are [1 to k]
        //if (use %) then k*i+1 = 1
        //therefore 1%1 = 2%1 = 3%1 = ....... = k%1= 0
        //thus to avoid this case use [childnode-(k*i+1)] to determine the index of childnode
        root->child[childnode - (k * i + 1)] = buildtree(preorder, childnode, n, k);
    }
    return root;
}
//preorder traversal
void printtree(Node *root, int *pre, int id, int k)
{
    if (!root)
        return;
    pre[id] = root->data;
    for (int i = 0; i < k; i++)
        if (root->child[i])
            printtree(root->child[i], pre, k * id + i + 1, k);
}

//print levelorder
void printlevelorder(Node *root, int k)
{
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        for (int i = 0; i < k; i++)
        {
            if (temp->child[i])
                q.push(temp->child[i]);
        }
    }
}

void testktree()
{
    int preorder[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(preorder) / sizeof(preorder[0]);
    int k = 3;
    Node *root = buildtree(preorder, 0, n, k);
    int pre[n];
    printtree(root, pre, 0, k);
    for (int i = 0; i < n; i++)
        cout << pre[i] << " ";

    cout << "\n";
    printlevelorder(root, k);
}

int main()
{
    testktree();
    return 0;
}