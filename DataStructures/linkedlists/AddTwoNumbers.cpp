#include<bits/stdc++.h>
using namespace std;
/**
 * You are given two non-empty linked lists representing two non-negative integers. 
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.You may assume the two numbers do not 
 * contain any leading zero, except the number 0 itself.
*/
class ListNode{
    public:
        int val;
        ListNode *next;
        ListNode(int val){
            this->val = val;
            next = NULL;
        }
};

class Solution{
    public:
     ListNode *addTwoNumber_II(ListNode *l1,ListNode *l2){
            if(!l1) return l2;
            if(!l2) return l1;
            int carry = 0;
            ListNode *dummy = new ListNode(0);
            ListNode *curr = dummy;

            while(l1 || l2){
                int x = l1?l1->val:0;
                int y = l2?l2->val:0;
                int sum = x + y + carry;

                carry = sum/10;
                curr->next = new ListNode(sum%10);
                curr = curr->next;
                if(l1) l1 = l1->next;
                if(l2) l2 = l2->next;
            }
            if(carry > 0)
               curr->next = new ListNode(carry);
            return dummy->next;
     }

     ListNode *addTwoNumber(ListNode *l1,ListNode *l2){
        if(!l1) return l2;
        if(!l2) return l1;

        ListNode *result = l1;
        int carry =0;
        while(l1 && l2){
            l1->val = l1->val + l2->val + carry;
            carry = l1->val/10;
            l1->val = l1->val%10;

            if(!l1->next && !l2->next){
                if(carry > 0)
                    l1->next = new ListNode(carry);
                break;
            }
            else if(!l1->next){
                l1->next = new ListNode(0);
            }
            else if(!l2->next){
                l2->next = new ListNode(0);
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        return result;
     }
};

int main(){
    ListNode *l1 = new ListNode(9);
    l1->next = new ListNode(3);
    ListNode *l2 = new ListNode(8);
    l2->next = new ListNode(9);
    //two numbers are : 39 and 98
    //so their sum : 39 + 98 = 137
    //result should be printed as 7 3 1
    ListNode *result = Solution().addTwoNumber_II(l1,l2);
    while(result){
        cout<<result->val<<" ";
        result = result->next;
    }
    cout<<"\n";
    return 0;
}