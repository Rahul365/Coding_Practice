#include <bits/stdc++.h>
using namespace std;
/*
A path in binary tree can start at any node and end at any node but it must be downward only.
*/
struct Node
{
    int data;
    Node *left, *right;
    Node(int _data = 0, Node *left = nullptr, Node *right = nullptr) : data(_data), left(left), right(right){};
};

int countKSumPathsUtil(Node *root, int sum, unordered_map<int, int> &mp, int currsum = 0)
{
    if (!root)
        return 0;
    int ret = 0;
    currsum += root->data;
    //currsum -> sum of current path
    if (mp.count(currsum - sum))
    {
        ret += mp[currsum-sum];
    }
    mp[currsum]++;
    if (root->left != nullptr)
    {
        ret += countKSumPathsUtil(root->left, sum, mp, currsum);
    }
    if (root->right != nullptr)
    {
        ret += countKSumPathsUtil(root->right, sum, mp, currsum);
    }
    mp[currsum]--;
    return ret;
}

int countKSumPaths(Node *root, int targetSum)
{
    unordered_map<int, int> mp;
    mp[0] = 1;
    int answer = countKSumPathsUtil(root, targetSum, mp);
    return answer;
}

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(1);
    root->left->right = new Node(2);
    root->right = new Node(-1);
    root->right->left = new Node(3);
    root->right->left->left = new Node(2);
    root->right->left->right = new Node(5);

    int k = 3;
    cout << "No of paths with sum equals to " << k
         << " are : " << countKSumPaths(root, k) << "\n";
    return 0;
}