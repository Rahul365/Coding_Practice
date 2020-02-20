#include<bits/stdc++.h>
using namespace std;

/**
 * As we know that using binary search tree gives you efficiency on storage of strings 
 * but compromises on time complexity. Ans using trie gives us better searching and insertion time complexity
 * but uses lot of storage.
 * Ternary Search Trees(TSTs) are combination of both Trie and Binary Search Tree.
 * Thus it provides better space complexity(of BST) and time complexity(of Trie).
 * 
 * Introduced by John Bentely and Sedgewick.
 * 
 * 
 * node declaration
 * 
 * TSTNode(data,isendofword,*left,*eq,*right);
 * data -> represents the character of a string at current node 
 * isendofword -> indicates ending of a string in tree
 * *left -> pointer that points to node whose data < currentnode's data
 * *eq -> pointer that points to node whose data == currentnode's data
 * *right -> pointer that points to node whose data > currentnode's data
*/

struct TSTNode{
    char data;
    bool isendofword;
    struct TSTNode *left,*eq,*right;
    
    TSTNode(char data)
    {
        this->data = data;
        isendofword = false;
        left = eq = right = NULL;
    }
};


/**
 * Fundamentals
 * After finding an empty node 
 * insert curren character in it
 * then follow the *eq pointer line
 * but before check 
 * if(is there any next character available?)
 * No -> this is the end of current string 
 *    mark endofword = true here and return
 * Yes -> insert(root->eq,w+1) 
 * 
*/
struct TSTNode *insert(struct TSTNode *root,char *w){
    if(!root)
    {
         root = new TSTNode(*w);
    }

    if(root->data > *w){
        root->left = insert(root->left,w);
    }
    else if(root->data < *w){
        root->right = insert(root->right,w);
    }
    else{
        if(!(*(w+1))) root->isendofword = true;
        else root->eq = insert(root->eq,++w);
    }
    return root;
}

bool searchinTST(struct TSTNode  *root,char *w){
    if(!root) return false;
    if(root->data > *w) 
        return searchinTST(root->left,w);
    else if(root->data < *w)
        return searchinTST(root->right,w);
    //else *w == root->data
    if(root->isendofword && !(*(w+1))) return true;
    return searchinTST(root->eq,++w);
}

bool searchinTSTII(struct TSTNode  *root,char *w){
    while(root){
        if(root->data > *w) root = root->left;
        else if(root->data < *w) root = root->right;
        else{
            if(root->isendofword && !(*(w+1))) return true;
            ++w;
            root = root->eq;
        }
    }
    return false;
}


/**
 * Traverse TST in inorder fashion to print the words in sorted order
*/
void displaywords(struct TSTNode *root,string s,vector<string> &words){
    if(!root) return;
    displaywords(root->left,s,words);
    
    if(root->isendofword){
        // cout<<(s + root->data)<<" ";
        words.push_back(s+root->data);
    }
    displaywords(root->eq,s+root->data,words);

    displaywords(root->right,s,words);
}



void print(const vector<string> &result){
    for(string s : result) cout<<s<<" , ";
    cout<<"  \n";
}


int main(){
    vector<string> w = {"lunatic","bobbafett","husky","bonding","woodoes"};
    struct TSTNode *root = NULL;
    for(string s : w) root = insert(root,&s[0]);

    string x = "husky";
    cout<<(searchinTST(root,&x[0])?"Yes":"No")<<"\n";
    cout<<(searchinTSTII(root,&x[0])?"Yes":"No")<<"\n";

    vector<string> result;
    displaywords(root,"",result);
    print(result);
    return 0;
}