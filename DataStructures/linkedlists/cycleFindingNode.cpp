#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int data){
        this->data = data;
        next = NULL;
    }
};

Node *cycleNode(Node  *head){
    if(!head || !head->next) return head;

    Node *slowptr = head,*fastptr = head;
    //initialize two pointers
    //slow = fast = head;
    //move slow pointer one at a time
    //and fast pointer two at a time
    while(slowptr->next && fastptr->next->next)
    {
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
        if(slowptr == fastptr) break;   
    }

    if(slowptr == fastptr){
        //set the slowptr to start
        slowptr = head;
    }

    Node *cyclestartnode = slowptr;
    while(cyclestartnode!=fastptr){
        cyclestartnode = cyclestartnode->next;
        fastptr = fastptr->next;
    }
    return cyclestartnode;
}

int main(){
    Node *head = new Node(1);
    Node *cyclenode  = head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = cyclenode;//connect 4->2
    cyclenode = cycleNode(head);

    /**
     *  (head)1->2->3->4->2(head)
    */
    if(cyclenode){
        cout<<cyclenode->data<<"\n";
    }
    else{
        cout<<"NULL\n";
    }
    return 0;
}