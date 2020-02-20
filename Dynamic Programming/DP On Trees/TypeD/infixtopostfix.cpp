/*   
   link : http://codeforces.com/problemset/problem/935/E
*/
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
bool isoperand(char ch){
    return ch>='0' && ch <= '9';
}

int prec(char ch){
    if(ch == '+' || ch == '-' || ch == '?')
        return 1;
    if(ch == '*' || ch == '/')
        return 2;
    if(ch == '^')
        return 3;
    return -1;
}

string infixtopostfix(string s){
    string ans = "";
    stack<char> stk;
    int n = s.length();
    for(int i =0 ;i<n;i++){
        if(isoperand(s[i])){
            ans+=s[i];
        }
        else if(s[i] == '('){
            stk.push(s[i]);
        }
        else if(s[i] == ')'){
            while(!stk.empty() && stk.top()!='('){
                ans += stk.top();
                stk.pop();
            }
            if(!stk.empty()) stk.pop();
        }
        else{
            //it's an operator
            while(!stk.empty() && prec(s[i]) <= prec(stk.top())){
                ans += stk.top();
                stk.pop();
            }
            stk.push(s[i]);
        }
    }
    while(!stk.empty()){
        ans += stk.top();
        stk.pop();
    }
    return ans;
}



class Node{
    public:
        char data;
        int operators;
        int mx[104];
        int mn[104];
        Node *left,*right;
        int p,m;
        Node(char data){
            p = m = 0;
            operators = !isoperand(data)?1:0;
            if(isoperand(data))
            {
                mx[0] = mn[0] = data - '0';
            }
            this->data = data;
            left=right=NULL;
        }
};


void MAX(int &x,int y){
    if(x < y) x = y;
}

void MIN(int &x,int y){
    if(x > y) x = y;
}

Node *convertPostfixtotree(string post,int p,int m){
    bool flag(false);//for p<=100
    if(m <= 100) flag = true;
    int n = post.length();
    stack<Node*> stk;
    for(int i = 0;i<n;i++){
        if(isoperand(post[i])){
            Node *newnode = new Node(post[i]);
            stk.push(newnode);
        }
        else{//it is operator
            Node *f = stk.top(); stk.pop();
            Node *s = stk.top(); stk.pop();
            Node *newnode = new Node(post[i]);
            newnode->left = s;
            newnode->right = f;
            newnode->operators += newnode->left->operators + newnode->right->operators;//number of operators to fill in the substree from newnode
            stk.push(newnode);
            int i_lim = min(100,newnode->operators);

            for(int i = 0;i <= i_lim; ++i){//total number of operators available for current node 
                newnode->mx[i] = -mod;
                newnode->mn[i] = mod;
                int j_lim = min(i,newnode->left->operators);
                for(int j = 0;j<=j_lim; ++j){//number of operators used in the left subtree
                    if(!flag){//if plus <= 100
                        if(i-j-1 <= newnode->right->operators && i!=j){
                            //if we use + operator
                            MAX(newnode->mx[i],newnode->left->mx[j] + newnode->right->mx[i-j-1]);
                            MIN(newnode->mn[i],newnode->left->mn[j] + newnode->right->mn[i-j-1]);
                        }
                        if(i-j <= newnode->right->operators){
                            //if we use - operator
                            MAX(newnode->mx[i],newnode->left->mx[j] - newnode->right->mn[i-j]);
                            MIN(newnode->mn[i],newnode->left->mn[j] - newnode->right->mx[i-j]);
                        }
                    }
                    else{//if minus <= 100
                        if(i-j <= newnode->right->operators){
                            //if we use + operator
                            MAX(newnode->mx[i],newnode->left->mx[j] + newnode->right->mx[i-j]);
                            MIN(newnode->mn[i],newnode->left->mn[j] + newnode->right->mn[i-j]);
                        }
                        if(i-j-1 <= newnode->right->operators && i!=j){
                            //if we use - operator
                            MAX(newnode->mx[i],newnode->left->mx[j] - newnode->right->mn[i-j-1]);
                            MIN(newnode->mn[i],newnode->left->mn[j] - newnode->right->mx[i-j-1]);
                        }
                    }   
                }
            }
        }
    }
    return stk.top();
}

void postorder(Node *root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data;
}




int main(){
    int p,m;
    string s;
    cin>>s>>p>>m;

    Node *root = convertPostfixtotree(infixtopostfix(s),p,m);
    int use = p;
    if(m <= 100) use = m;
    cout<<root->mx[use]<<"\n";

    return 0;
}