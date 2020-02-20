#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};
//recursive approach
Node* reverseinpairs(Node *head){
    if(!head || !head->next) return head;

    Node *b = head->next;//second node
    //connect second -> first
    //but first do connect first->next to the rest of the list swapped in pairs
    head->next = reverseinpairs(head->next->next);
    b->next = head;
    head = b;
    return head;
}

Node *reverseinpairsitr(Node *head){
    if(!head || !head->next) return head;
    Node *newhead = NULL;
    Node *prevlastNode = NULL;
    // a->b->c->d
    while(head && head->next){
        Node *c = head->next->next;//store c node
        if(!newhead) newhead = head->next;//b->........
        if(prevlastNode) prevlastNode->next = head->next;
        head->next->next = head; //make b->a
        head->next = c;//make b->(a->c)
        prevlastNode = head;//a
        head = head->next;//move to head of next pair
    }
    return newhead;
}

void printlist(Node *head){
    if(!head) return;
    while(head){
        cout<<head->data<<" ";
        head = head->next;
    }

    cout<<"\n";
}

int main(){
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    // head->next->next->next->next->next = new Node(6);
    printlist(head);
    head = reverseinpairsitr(head);
    printlist(head);
    return 0;
}