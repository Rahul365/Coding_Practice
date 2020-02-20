#include<bits/stdc++.h>
using namespace std;
class ListNode{
    public:
      int val;
      ListNode *next;
      ListNode (int x){
          val = x;
          next = NULL;
      }
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    
    ListNode* reverselist(ListNode* head){
        if(!head || !head->next) return head;
        ListNode *prev = NULL,*curr = NULL;
        while(head){
            curr = head->next;
            head->next = prev;
            prev = head;
            head = curr;
        }
    
        return prev;//reversed list head
    }
    //recursive approach
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || !head->next) return head;
        ListNode *newhead = NULL;
        
        ListNode *temp = head;
        int j = 1;
        while(temp && j < k){
            temp = temp->next;
            j++;
        }
        if(!temp && j<=k) return head;
        ListNode *nexthead=NULL,*prevhead = NULL;
        prevhead = head;
        if(temp)
        {
            nexthead = temp->next;
            temp->next = NULL;
        }
        head = reverselist(head);
        if(!newhead) newhead = head;
        prevhead->next = reverseKGroup(nexthead,k);
        
        return newhead;
    }

    ListNode *reversenodeinkgroupsiterative(ListNode *head,int k){
        if(!head || !head->next) return head;

        ListNode *prevblocklastnode = NULL;
        ListNode *nextblockhead = NULL;
        ListNode *newhead = NULL;
        while(head){
            ListNode *temp = head;
            int j = 1;
            while(temp && j<k){
                temp = temp->next;
                j++;
            }
            if(!temp && j<=k){//can't reverse a block of length less than k
                if(prevblocklastnode) prevblocklastnode->next = head;
                if(!newhead) newhead = head;
                break;
            }
            if(temp){
                nextblockhead = temp->next;
                temp->next = NULL;
                //unlink current block from the rest of the list and store the next head node
            }
            
            ListNode *revhead = reverselist(head);//reverse the current block
            if(!newhead) newhead = revhead;
            if(prevblocklastnode) prevblocklastnode->next = revhead;
            prevblocklastnode = head;//set the previous block last node as current block's last node 
            //as it will be needed for the next block
            head = nextblockhead;//move the head to the next block's head
        }
        return newhead;
    }
};

void printlist(ListNode *head){
    while(head){
        cout<<head->val<<" ";
        head = head->next;
    }
    cout<<"\n";
}

int main(){
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    printlist(head);
    head = Solution().reversenodeinkgroupsiterative(head,3);
    printlist(head);
    return 0;
}