#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/contest/1324/problem/D
// Balance factor = 4
struct Node{
        ll cnt;
        ll size;
        ll data;
        ll h;
        Node *left,*right;
        Node(){
            
        }
        Node(ll _data){
            h = 0;
            size = cnt = 0;
            data = _data;
            left = right = NULL;
        }
};

ll sof(Node *x){
    return x?x->size : 0;
}

ll hof(Node *x){
    return x?x->h:0;
}

Node *rotateleft(Node *x){
    Node *w = x->left;
    x->left =w->right;
    w->right = x;
    x->h = 1  + max(hof(x->left),hof(x->right));
    x->size = x->cnt + sof(x->left) + sof(x->right);
    w->h = 1 + max(hof(w->left),x->h);
    w->size = w->cnt + sof(w->left) + x->size;
    return w;
}


Node *rotateright(Node *x){
    Node *w = x->right;
    x->right =w->left;
    w->left = x;
    x->h = 1  + max(hof(x->left),hof(x->right));
    x->size = x->cnt + sof(x->left) + sof(x->right);
    w->h = 1 + max(hof(w->right),x->h);
    w->size = w->cnt + sof(w->right) + x->size;
    return w;
}

Node *doubleleft(Node *x){
     x->left = rotateright(x->left);
     return rotateleft(x);   
}

Node *doubleright(Node *x){
    x->right = rotateleft(x->right);
    return rotateright(x);
}

void insert(Node *&root,ll data){
    if(!root){
        root = new Node(data);
    }
    if(root->data < data){
        insert(root->right,data);
        if(hof(root->right) - hof(root->left)>3){
            if(root->data < root->right->data){
                root = rotateright(root);
            }
            else{
                root = doubleright(root);
            }
        }
    }
    else if(root->data > data){
        insert(root->left,data);
        if(hof(root->left) - hof(root->right)>3){
            if(root->data > root->left->data){
                root = rotateleft(root);
            }
            else{
                root = doubleleft(root);
            }
        }
    }
    else{
         ++root->cnt;
    }
    root->size = root->cnt + sof(root->left)  +sof(root->right);
    root->h = 1 + hof(root->left) + hof(root->right);
}

ll smallerthan(Node *root,ll data){
    if(!root) return 0;
    
    if(root->data < data){
        return sof(root->left)
            + root->cnt + smallerthan(root->right,data);
    }
    else if(root->data > data){
        return smallerthan(root->left,data);
    }
    return sof(root->left);
}

void inorder(Node *root){
    //L N R
    stack<Node*> stk;
    while(true){
        while(root){
            stk.push(root); root =  root->left;
        }
        if(stk.empty()) break;
        root = stk.top(); stk.pop();
        cout << root->data <<" ";
        root = root->right;
    }
    cout <<"\n";
}

void solveii(){
    int n;
        cin >> n;
        vector<long long> c(n);
        for(int i = 0;i<2*n;++i) {
            int x;
            cin >> x;
            c[i>=n?i-n:i] += (x * (i>=n?-1:1));
        }
        sort(c.begin(),c.end());
        //ci  > -cj  -> ci + cj > 0 , j > i
        long long ans = 0;
        for(int i= 0;i<n;++i){
            int l =  i+ 1;
            int r =  n- 1;
            int pos = -1;
            while(l<=r){
                int m = l +(r-l)/2;
                if(c[i]+c[m] <= 0){
                    l = m+1;
                }
                else{
                    pos = m;
                    r =  m-1;
                }
            }
            if(pos != -1){
                ans+=(n-pos);
            }  
        }
        cout << ans <<"\n";
}

void solveusingAVL(){
    int n;
    cin >> n;   
    vector<ll> a(n),b(n);
    for(int i= 0;i<n;++i) cin >> a[i];
    for(int i= 0;i<n;++i) cin >> b[i];
    ll ans = 0;
    Node *root = NULL;
    for(int i = n-1;i>=0;--i){
        ll c = a[i] - b[i];
        ll cc = smallerthan(root,c);
        if(cc > 0)
            ans+=cc;
        insert(root,-c);
    }
    //inorder(root);
    cout << ans <<"\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solveusingAVL();
    solveii();
    return 0;
}