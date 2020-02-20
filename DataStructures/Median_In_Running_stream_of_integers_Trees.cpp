#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    int size;
    int c;
    int height;
    Node *left,*right;
    Node(int data){
        size = 0;
        height = 0;
        c = 1;
        this->data = data;
        left = right = NULL;
    }
};

int Height(Node *root){
    if(!root){
        return 0;
    }
    else{
        return root->height;
    }
}

int Size(Node *root){
    if(!root)
        return 0;
    else
        return root->size;
}

struct Node *singlerotateleft(Node *x){
    Node *w = x->left;
    x->left = w->right;
    w->right = x;
    x->height = max(Height(x->left),Height(x->right))+1;
    x->size = Size(x->left) + Size(x->right) + x->c;
    w->height = max(Height(w->left),x->height)+1;
    w->size = Size(w->right) + x->size + w->c; 
    return w;
}

struct Node *singlerotateright(Node *x){
    Node *w = x->right;
    x->right = w->left;
    w->left = x;
    x->height = max(Height(x->left),Height(x->right))+1;
    x->size = Size(x->left) + Size(x->right) + x->c;
    w->height = max(x->height,Height(w->right))+1;
    w->size = Size(w->right) + x->size + w->c; 
    return w;
}

struct Node *doublerotateleft(Node *z){
    z->left = singlerotateright(z->left);
    return singlerotateleft(z);
}

struct Node *doublerotateright(Node *z){
    z->right = singlerotateleft(z->right);
    return singlerotateright(z);
}

Node *insert(Node *root,int data){
    if(!root)
        root =  new Node(data);
    else if(root->data == data)
    {
        root->c++;
    }
    else if(root->data > data){
        root->left = insert(root->left,data);
        if((Height(root->left) - Height(root->right)) == 2){
            if(data < root->left->data){
                root = singlerotateleft(root);
            }
            else{
                root = doublerotateleft(root);
            }
        }
    }
    else if(root->data < data){
        root->right = insert(root->right,data);
        if((Height(root->right) - Height(root->left)) == 2){
            if(data > root->right->data){
                root = singlerotateright(root);
            }
            else{
                root = doublerotateright(root);
            }
        }
    }
    root->height = max(Height(root->left),Height(root->right))+1;
    root->size = Size(root->left) + Size(root->right) + root->c;
    return root;
}

Node *findKth(Node *root,int k){
    if(!root) return NULL;
    int r = Size(root->left);
    if(r+1 <= k && k<= r + root->c){
        return root;
    }
    else if(k < r+root->c){
        return findKth(root->left,k);
    }
    else if(k > r+root->c){
        return findKth(root->right,k-(r+root->c));
    }
}

void inorder(Node *root){
    if(!root)
        return;
    inorder(root->left);
    cout<<root->data<< ","<<root->size<<"/";
    inorder(root->right);
}

void solveUsingBSTAndAugumentedTrees(){
    int n;
    cin>>n;
    int x;
    Node *root = NULL;
    for(int i = 1;i<=n;i++){
        cin>>x;
        root = insert(root,x);
        
        int mid = 1 + (i-1)/2;
        if(i&1){
            cout<<findKth(root,mid)->data<<"\n";
        }
        else{
            int ans = findKth(root,mid)->data + findKth(root,mid+1)->data;
            cout<<(ans>>1)<<"\n";
        }
    }
}








struct Heap{
    int *a;
    int count;
    int size;
    bool type;
    Heap(int size,bool type){
        a = new int[size];
        count = 0;
        this->size = size;
        this->type = type;
        
    }
};

struct Heap *createMinHeap(int n){
    return new Heap(n,true);
}

struct Heap *createMaxHeap(int n){
    return new Heap(n,false);
}

int parent(Heap *h,int i){
    if(i<=0 && i>=h->count){
        return -1;
    }
    return (i-1)>>1;
}

int left(Heap *h,int i){
    int l = 2*i+1;
    return (l>=h->count?-1:l);
}

int right(Heap *h,int i){
    int r = 2*i+2;
    return (r >= h->count?-1:r);
}

void prelocatedown(Heap *h,int i){
    int l = left(h,i);
    int r = right(h,i);
    int min = i;
    int max = i;
    if(h->type){
        if(l!=-1 && h->a[l] < h->a[min]){
            min = l;
        }
        if(r!=-1 && h->a[r] < h->a[min]){
            min = r;
        }
        if(min!=i){
            swap(h->a[i],h->a[min]);
            prelocatedown(h,min);
        }
    }else{
        if(l!=-1 && h->a[l] > h->a[max]){
            max = l;
        }
        if(r!=-1 && h->a[r] > h->a[max]){
            max = r;
        }
        if(max!=i){
            swap(h->a[i],h->a[max]);
            prelocatedown(h,max);
        }
    }
}

int getTop(Heap *h){
    return (h->count == 0)?-1:h->a[0];
}

int deleteTop(Heap *h){
    if(h->count == 0) return -1;
    int data = h->a[0];
    h->a[0] = h->a[h->count-1];
    h->count--;
    prelocatedown(h,0);
    return data;
}

void resizeHeap(Heap *h){
    if(!h) return;
    int *a = h->a;
    h->a = new int[h->size * 2];
    for(int i = 0;i<h->size;i++)
        h->a[i] = a[i];
    h->size *= 2;
    delete(a);
}

void insert(Heap *h,int data){
    if(h->count == h->size){
        resizeHeap(h);
    } 
    h->count++;
    int i = h->count - 1;
    if(h->type){
        while(i>0 && h->a[(i-1)>>1] > data){
            h->a[i] = h->a[(i-1)>>1];
            i = (i-1)>>1;
        }
        h->a[i] = data;
    }
    else{
        while(i>0 && h->a[(i-1)>>1] < data){
            h->a[i] = h->a[(i-1)>>1];
            i = (i-1)>>1;
        }
        h->a[i] = data;
    }
    
}

int signnum(int x,int y){
    if(x == y)
        return 0;
    return (x < y)?-1:1;
}

void solveUsingHeap(){
    int n;
    int x;
    cin>>n;
    int m = 0;
    Heap *hmin = createMinHeap(n);
    Heap *hmax = createMaxHeap(n);
    while(n--){
        cin>>x;
        // cout<<hmax->count<<" "<<hmin->count<<"\n";
        int sign = signnum(hmax->count,hmin->count);
        switch(sign){
            case 1://number of elements in the left(max) heap are more than right(min) heap
                if(x < m){//fits in the left
                    insert(hmin,deleteTop(hmax));
                    insert(hmax,x);
                }
                else{
                    insert(hmin,x);
                }
                m = (getTop(hmax) + getTop(hmin))>>1;
                break;
            case 0://number of elements are equal on both heaps
                if(x < m){
                    insert(hmax,x);
                    m = getTop(hmax);
                }
                else{
                    insert(hmin,x);
                    m = getTop(hmin);
                }
                break;
            case -1:
                if(x < m){
                    insert(hmax,x);
                }
                else{
                    insert(hmax,deleteTop(hmin));
                    insert(hmin,x);
                }
                m = (getTop(hmax) + getTop(hmin))>>1;
                break;
        }
        cout<<m<<"\n";
    }
}



int main(){
    solveUsingHeap();
    return 0;
}






