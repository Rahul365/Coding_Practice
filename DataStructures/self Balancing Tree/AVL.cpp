#include <bits/stdc++.h>
using namespace std;
/*generic AVL tree template*/
namespace csm
{
    template <typename T>
    struct TreeNode
    {
        TreeNode *m_left, *m_right;
        T m_data;     //data stored at the node
        int m_size;   //size of subtree starting at this node
        int m_height; //max height of tree starting from this node
        TreeNode(T data, TreeNode *left = nullptr, TreeNode *right = nullptr)
            : m_data(data), m_left(left), m_right(right) {}

        static int getHeight(TreeNode<T> *x)
        {
            return x ? x->m_height : 0;
        }

        static int getSize(TreeNode<T> *x)
        {
            return x ? x->m_size : 0;
        }
        /*
            compare A with B:
            return  0 : if A == B
            return -1 : if A < B
            return  1 : if A > B
        */
        static int Compare(T A, T B)
        {
            //comparison logic for search
            if (A.first >= B.second)
                return 1;
            else if (A.second <= B.first)
                return -1;
            return 0;
            // return a->m_data < b->m_data ? -1 : (a->m_data == b->m_data?0:1);
        }
    };

    template <typename T>
    void inorder(TreeNode<T> *root)
    {
        if (!root)
            return;
        inorder(root->m_left);
        cout << root->m_data.first << " " << root->m_data.second << " \n ";
        inorder(root->m_right);
    }

    template <typename T>
    class AVLTree
    {
        TreeNode<T> *m_root;

    public:
        AVLTree()
        {
            m_root = nullptr;
        }
        TreeNode<T> *getRoot()
        {
            return m_root;
        }
        void insert(T data);
        TreeNode<T> *insertUtil(TreeNode<T> *root, T data);
        TreeNode<T> *find(T data);
        TreeNode<T> *findUtil(TreeNode<T> *root, T data);
        TreeNode<T> *Lrotation(TreeNode<T> *root);
        TreeNode<T> *Rrotation(TreeNode<T> *root);
        TreeNode<T> *LRrotation(TreeNode<T> *root);
        TreeNode<T> *RLrotation(TreeNode<T> *root);
    };
    template <typename T>
    TreeNode<T> *AVLTree<T>::Lrotation(TreeNode<T> *root)
    {
        if (!root)
            return root;
        TreeNode<T> *x = root->m_left;
        root->m_left = x->m_right;
        x->m_right = root;
        root->m_size = 1 + TreeNode<T>::getSize(root->m_left) + TreeNode<T>::getSize(root->m_right);
        root->m_height = 1 + max(TreeNode<T>::getHeight(root->m_left), TreeNode<T>::getHeight(root->m_right));
        x->m_size = 1 + TreeNode<T>::getSize(x->m_left) + TreeNode<T>::getSize(x->m_right);
        x->m_height = 1 + max(TreeNode<T>::getHeight(x->m_left), TreeNode<T>::getHeight(x->m_right));
        return x;
    }
    template <typename T>
    TreeNode<T> *AVLTree<T>::Rrotation(TreeNode<T> *root)
    {
        if (!root)
            return root;
        TreeNode<T> *x = root->m_right;
        root->m_right = x->m_left;
        x->m_left = root;
        root->m_size = 1 + TreeNode<T>::getSize(root->m_left) + TreeNode<T>::getSize(root->m_right);
        root->m_height = 1 + max(TreeNode<T>::getHeight(root->m_left), TreeNode<T>::getHeight(root->m_right));
        x->m_size = 1 + TreeNode<T>::getSize(x->m_left) + TreeNode<T>::getSize(x->m_right);
        x->m_height = 1 + max(TreeNode<T>::getHeight(x->m_left), TreeNode<T>::getHeight(x->m_right));
        return x;
    }
    template <typename T>
    TreeNode<T> *AVLTree<T>::find(T data)
    {
        return findUtil(m_root, data);
    }
    template <typename T>
    TreeNode<T> *AVLTree<T>::findUtil(TreeNode<T> *root, T data)
    {
        if (!root)
            return root;
        int comp = TreeNode<T>::Compare(data, root->m_data);
        if (comp < 0)
        {
            return findUtil(root->m_left, data);
        }
        else if (comp > 0)
        {
            return findUtil(root->m_right, data);
        }
        return root;
    }
    template <typename T>
    TreeNode<T> *AVLTree<T>::LRrotation(TreeNode<T> *root)
    {
        if (!root)
            return root;
        root->m_right = Lrotation(root->m_right);
        return Rrotation(root);
    }
    template <typename T>
    TreeNode<T> *AVLTree<T>::RLrotation(TreeNode<T> *root)
    {
        if (!root)
            return root;
        root->m_left = Rrotation(root->m_left);
        return Lrotation(root);
    }
    template <typename T>
    void AVLTree<T>::insert(T data)
    {
        m_root = insertUtil(m_root, data);
    }

    template <typename T>
    TreeNode<T> *AVLTree<T>::insertUtil(TreeNode<T> *root, T data)
    {
        if (!root)
        {
            root = new TreeNode(data);
        }
        else if (TreeNode<T>::Compare(root->m_data, data) < 0)
        {
            root->m_right = insertUtil(root->m_right, data);
            if (TreeNode<T>::getHeight(root->m_right) - TreeNode<T>::getHeight(root->m_left) > 2)
            {
                if (root->m_right->m_data <= data)
                {
                    /*Node is inserted in the right subtree of right child*/
                    //right rotation to be done here
                    root = Rrotation(root);
                }
                else
                {
                    /*Node is inserted in the left subtree of right child*/
                    root = LRrotation(root);
                }
            }
        }
        else if (TreeNode<T>::Compare(root->m_data, data) > 0)
        {
            root->m_left = insertUtil(root->m_left, data);
            if (TreeNode<T>::getHeight(root->m_left) - TreeNode<T>::getHeight(root->m_left) > 2)
            {
                if (root->m_left->m_data >= data)
                {
                    /*Node is inserted in the left subtree of left child*/
                    //left rotation to be done here
                    root = Lrotation(root);
                }
                else
                {
                    /*Node is inserted in the right subtree of left child*/
                    root = RLrotation(root);
                }
            }
        }
        root->m_size = 1 + TreeNode<T>::getSize(root->m_left) + TreeNode<T>::getSize(root->m_right);
        root->m_height = 1 + max(TreeNode<T>::getHeight(root->m_left), TreeNode<T>::getHeight(root->m_right));
        return root;
    }

};

int main()
{
    return 0;
}