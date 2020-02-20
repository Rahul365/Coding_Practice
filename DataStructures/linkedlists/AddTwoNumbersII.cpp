#include<bits/stdc++.h>
using namespace std;

class ListNode{
    public:
     int val;
     ListNode *next;
     ListNode(int x) : val(x),next(NULL) {}
};

class  Solution{
    public:
    ListNode *addTwoNumbers(ListNode *l1,ListNode *l2){
        if(!l1) return l2;
        if(!l2) return l1;

        ListNode *result = l1;

        stack<ListNode*> stk1,stk2;

        while(l1){
            stk1.push(l1);
            l1 = l1->next;
        }

        while(l2){
            stk2.push(l2);
            l2 = l2->next;
        }

        ListNode *node = NULL;
        int carry = 0;

        while(!stk1.empty() && !stk2.empty()){
            ListNode *A = stk1.top(); stk1.pop();
            ListNode *B = stk2.top(); stk2.pop();

            A->val = A->val + B->val + carry;
            carry = A->val / 10;
            A->val = A->val % 10;

            if(stk1.empty() && stk2.empty()){
                if(carry > 0){
                    node = new ListNode(carry);
                    node->next = A;
                    A = node;
                }
                result = A;
                break;
            }
            else if(stk1.empty()){
                node = new ListNode(0);
                node->next = A;
                stk1.push(node);
            }
            else if(stk2.empty()){
                node = new ListNode(0);
                node->next = B;
                stk2.push(node);
            }

        }

        return result;
    }

     ListNode* addTwoNumbers_II(ListNode* l1, ListNode* l2) {
        if(!l1) return l2;
        if(!l2) return l1;
        
        ListNode *head = NULL,*temp = NULL;
        
        stack<ListNode*> stk1,stk2;
        
        while(l1) { stk1.push(l1); l1 = l1->next; }
        while(l2) { stk2.push(l2); l2 = l2->next; }
        
        int carry = 0;
        
        while(!stk1.empty() || !stk2.empty()){
            int x = stk1.empty()?0:stk1.top()->val;
            int y = stk2.empty()?0:stk2.top()->val;
            int sum = x + y + carry;
            carry = sum/10;
            
            if(head){
                temp = new ListNode(sum%10);
                temp->next =  head;
                head = temp;
            }
            else{
                head = new ListNode(sum%10);
            }
            if(!stk1.empty()) stk1.pop();
            if(!stk2.empty()) stk2.pop();
        }
        
        if(carry > 0){
            temp = new ListNode(carry);
            temp->next = head;
            head = temp;
        }
        return head;
    }
};

ListNode *getNumList(int num){
    ListNode *head = NULL;
    while(num!=0){
        int x = num % 10;//get the last digit
        ListNode *node = new ListNode(x);
        node->next = head;
        head = node;
        num = num / 10;//remove the last digit from the number
    }
    return head;
}

int main(){
    //num1 = 1234
    //num2 = 99876
    ListNode *l1 = getNumList(1234);
    

    ListNode *l2 = getNumList(99876);


    ListNode *result = Solution().addTwoNumbers(l1,l2);

    while(result){
        cout<<result->val<<" ";
        result = result->next;
    }
    cout<<"\n";
    
    return 0;
}