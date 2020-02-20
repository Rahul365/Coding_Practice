#include<bits/stdc++.h>
using namespace std;

struct Node{
        int data;
        Node *next;

        Node(int data){
            this->data = data;
            next  = NULL;
        }
};

/*Merge two lists*/
Node *sortedMerge(Node *a,Node *b){
    Node *result = NULL;
    if(!a)
        return b;
    if(!b)
        return a;
    if(a->data <= b->data){
        result = a;
        result->next = sortedMerge(a->next,b);
    }
    else{
        result = b;
        result->next = sortedMerge(a,b->next);
    }
    return result;
}

/*Divide the list into two halfs and set the head of two halfs*/
void frontAndBackSplit(Node *root,Node **front,Node **back){
    if(!root)
      return;
  
    Node *slow = root;
    Node *fast = root;
   
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
  

    *front = root;
    *back = slow->next;
    slow->next = NULL;
   
}


void mergesort(Node **href){
    Node *head = *href;
    if(!head || !head->next)
        return;
    Node *a = NULL;
    Node *b = NULL;

    frontAndBackSplit(head,&a,&b);

    mergesort(&a);
    mergesort(&b);

    *href = sortedMerge(a,b);
}


int main(){
    Node *list;
    list = new Node(5);
    list->next = new Node(3);
    list->next->next = new Node(2);
    list->next->next->next = new Node(1);
    mergesort(&list);
    while(list){
        cout<<list->data<<" ";
        list = list->next;
    }
    cout<<"\n";
    return 0;
}