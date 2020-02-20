#include<bits/stdc++.h>
using namespace std;
const int ALPHABETS = 26;

struct Trie{
    bool endofword;
    int weight;
    Trie *children[ALPHABETS];
    Trie(){
        endofword = false;
        weight = -1;
        for(int i = 0;i<ALPHABETS;i++)
            children[i] = NULL;
    }
};


void insert(Trie *root,string s,int weight){
    if(!root) return;
    for(int i = 0;i<s.length();i++){
        if(!root->children[s[i]-'a']){
            root->children[s[i]-'a'] = new Trie();
        }
        root = root->children[s[i]-'a'];
    }
    root->weight = max(root->weight,weight);
    root->endofword = true;
}


int getweight(Trie *root){
    if(!root) return -1;
    int weight = -1;
    if(root->endofword)
           weight = max(weight,root->weight);
    for(int i = 0;i<ALPHABETS;i++){
        if(root->children[i]){
            weight = max(weight,getweight(root->children[i]));
        }
    }
    return weight;
}

int search(Trie *root,string s){
    if(!root) return -1;
    int weight = -1;
    for(int i = 0;i<s.length();i++){
        if(!root->children[s[i]-'a']) return weight;
        if(root->endofword) weight = max(weight,root->weight);
        root = root->children[s[i]-'a'];
    }
    if(!root->endofword && root->weight!=-1)//if the prefix has been processed before
       return max(weight,root->weight);

    Trie *node = root;//store the end of given prefix 
    /* Recursive approach to find the string with heavy weight value for given prefix
    for(int i = 0;i<ALPHABETS;i++){
        if(root->children[i]){
            weight = max(weight,getweight(root->children[i]));
        }
    }
    */
    
    queue<Trie*> q;
    q.push(root);
    while(!q.empty()){
        Trie *node  = q.front();
        q.pop();
        if(node->endofword){
            weight = max(weight,node->weight);
        }
        for(int i = 0;i<ALPHABETS;i++){
            if(node->children[i])
                 q.push(node->children[i]);
        }
    }

    node->weight = weight;//set the weight of given prefix to avoid processing for the same prefix again
    return weight;
}



int main(){
    int n,q;
    cin>>n>>q;
    string s;
    int weight;
    Trie *root = new Trie();
    while(n--){
        cin>>s>>weight;
        insert(root,s,weight);
    }
    while(q--){
        cin>>s;
        cout<<search(root,s)<<"\n";
    }
    return 0;
}