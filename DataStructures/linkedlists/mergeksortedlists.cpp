#include<bits/stdc++.h>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x),next(NULL){}
};

struct compare{
    bool operator()(struct ListNode* a,struct ListNode* b){
        return a->val > b->val;
    }    
};

class Solution {
public:
    
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        ListNode* newhead = NULL,*crawler = NULL;
        priority_queue<ListNode*,vector<ListNode*>,compare> q;
        for(ListNode *x : lists){
            if(x)
                q.push(x);
        }
        while(!q.empty()){
            ListNode *temp = q.top();
            q.pop();
           if(temp && temp->next){
               q.push(temp->next);
           }
            if(!newhead){
                newhead = temp;
                crawler = temp;
            }
            else{
                crawler->next = temp;
                crawler = temp;
            }
        }
       
        return newhead;
    }

    ListNode *sortedmerge(ListNode *a,ListNode *b){
        if(!a) return b;
        if(!b) return a;
        ListNode *head = NULL;
        
        if(a->val <= b->val){
            head = a;
            head->next = sortedmerge(a->next,b);
        }
        else{
            head = b;
            head->next = sortedmerge(a,b->next);
        }
        return head;
    }
    
    //using traditional merge procedure
    ListNode* mergeKListsII(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        int n = lists.size();
        
        ListNode *newhead = NULL;
        
        int i = 0;
        for(;i+1<n;i+=2){
            newhead = sortedmerge(newhead,sortedmerge(lists[i],lists[i+1]));
        }
        if(n&1)
            newhead = sortedmerge(newhead,lists[i]);
        return newhead;
    }
};