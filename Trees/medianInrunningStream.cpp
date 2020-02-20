#include<bits/stdc++.h>
using namespace std;

struct avltree{
    int data;
    int size;//size of the tree from this node
    int cnt;//number of occurences of data
    int height;//height of the tree from this node
    struct avltree *left,*right;
    avltree(int data){
        cnt = 1;
        size = 0;
        height = 0;
        this->data = data;
        left = right = NULL;
    }
};

int Height(struct avltree *root){
    if(!root) return 0;
    return root->height;
}

int Size(struct avltree  *root){
    if(!root) return 0;
    return root->size;
}

struct avltree  *rotateleft(struct avltree *x){
    struct avltree *w = x->left;
    x->left = w->right;
    w->right = x;
    x->height = max(Height(x->left),Height(x->right))+1;
    x->size = Size(x->left) + Size(x->right) + x->cnt;
    w->height = max(Height(w->left),x->height) + 1;
    w->size = Size(w->left) + x->size + w->cnt;
    return w;
}

struct avltree *rotateright(struct avltree *x){
    struct avltree *w = x->right;
    x->right = w->left;
    w->left = x;
    x->height = max(Height(x->left),Height(x->right)) + 1;
    x->size = Size(x->left) + Size(x->right) + x->cnt;
    w->height = max(x->height,Height(w->right))  + 1;
    w->size = x->size + Size(w->right) + w->cnt;
    return w;
}   

struct avltree *doublerotateleft(struct avltree *z){
    z->left = rotateright(z->left);
    return rotateleft(z);    
}

struct avltree * doublerotateright(struct avltree  *z){
    z->right = rotateleft(z->right);
    return rotateright(z);
}

struct avltree *insert(struct avltree *root,int data){
    if(!root){
        root = new avltree(data);
    }
    else if(root->data == data){
        ++root->cnt;
    }
    else if(root->data  < data){
        root->right = insert(root->right,data);
        if(Height(root->right) - Height(root->left) == 2){
            if(root->right->data < data){
                root = rotateright(root);
            }
            else{
                root = doublerotateright(root);
            }
        }
    }
    else if(root->data > data){
        root->left = insert(root->left,data);
        if(Height(root->left) - Height(root->right)== 2){
            if(root->left->data > data){
                root = rotateleft(root);
            }
            else{
                root = doublerotateleft(root);
            }
        }
    }
    
    root->size = Size(root->left) + Size(root->right) + root->cnt;
    root->height = max(Height(root->left),Height(root->right)) + 1;
    return root;
}

int findkth(struct avltree *root,int k){
    while(root){
        int l = Size(root->left);
        int r = l+root->cnt;/*size of left substree + root->cnt*/
        // cout<<l<<" "<<r<<"\n";
        if(l+1<= k && k <= r){
            return root->data;
        }
        else if(k < r){
            root = root->left;
        }
        else{
            k = k-r;
            root = root->right;
        }
    }
    return -1;
}

int main(){
    int t;
    cin>>t;
    struct avltree *root = NULL;
    while(t--){
        int data;
        cin>>data;
        root = insert(root,data);
        int k = root->size;
        int mid = 1 + (k-1)/2;
        if(k & 1){
            cout<<findkth(root,mid)<<"\n";
        }
        else{

            cout<<(findkth(root,mid)+findkth(root,mid+1) >> 1)<<"\n";
        }
    }
    return 0;
}