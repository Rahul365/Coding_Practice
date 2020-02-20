#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next, *random;
    Node(int data)
    {
        this->data = data;
        next = random = NULL;
    }
};

void printlist(Node *head)
{
    while (head)
    {
        cout << "(" << head->data << "," << (head->random ? head->random->data : -1) << ") ";
        head = head->next;
    }
    cout << "\n";
}

Node *copylist(Node *head)
{
    if (!head)
        return NULL;
    Node *copyhead = NULL, *newhead = NULL;
    Node *temp = head;
    //------first copy the list as you copy a single linked list without considering random pointers
    unordered_map<Node *, Node *> nodemap;
    newhead = copyhead = new Node(temp->data); //initialize the head of new copy
    nodemap[temp] = copyhead;
    temp = temp->next;
    while (temp)
    {
        copyhead->next = new Node(temp->data);
        copyhead = copyhead->next;
        nodemap[temp] = copyhead;
        temp = temp->next;
    }

    //-----now copy radom pointers using map
    copyhead = newhead;
    temp = head;
    while (temp)
    {
        copyhead->random = nodemap[temp->random];
        copyhead = copyhead->next;
        temp = temp->next;
    }

    return newhead;
}

Node *copylistWithoutMap(Node *head)
{
    //using Constant Space
    if (!head)
        return NULL;

    Node *newhead = head;
    Node *ptr = head;
    Node *cptr = NULL;
    while (ptr)
    {
        cptr = new Node(ptr->data);
        Node *nextptr = ptr->next;
        ptr->next = cptr;
        cptr->next = nextptr;
        ptr = nextptr;
    }

    ptr = newhead;
    cptr = ptr->next;
    while (cptr->next)
    {
        cptr->random = (ptr->random ? ptr->random->next : NULL);
        ptr = ptr->next->next;
        cptr = cptr->next->next;
    }
    if (cptr)
    {
        cptr->random = (ptr->random ? ptr->random->next : ptr->random);
    }
    ptr = newhead;
    cptr = newhead->next;
    newhead = cptr;
    while (cptr->next)
    {
        ptr->next = ptr->next->next;
        cptr->next = cptr->next->next;
        ptr = ptr->next;
        cptr = cptr->next;
    }
    if (ptr->next)
        ptr->next = NULL;
    return newhead;
}

bool verify(Node *copy, Node *head, map<Node *, bool> &mark)
{
    while (copy && mark.find(copy) == mark.end())
    {
        bool condition = (copy->data == head->data && ((!head->random && !copy->random) || head->random->data == copy->random->data));
        if (!condition)
            return false;
        copy = copy->next;
        head = head->next;
    }
    return !copy;
}

bool verify(Node *copy, Node *head)
{
    while (copy != head && copy->data == head->data)
    {
        copy = copy->next;
        head = head->next;
    }
    return copy == head;
}

int main()
{
    map<Node *, bool> mark;
    Node *head = new Node(1);
    mark[head] = true;
    Node *a = head->next = new Node(2);
    mark[a] = true;
    Node *b = a->next = new Node(3);
    mark[b] = true;
    Node *c = b->next = new Node(4);
    mark[c] = true;
    // 1-> 2(a) -> 3(b) -> 4(c)
    head->random = c; //1 => 4
    b->random = a;    //3 => 2
    a->random = c;    //2 => 4
    // printlist(head);
    // Node *chead = copylist(head);
    // printlist(chead);
    Node *copy = copylistWithoutMap(head);
    if (verify(copy, head))
    {
        cout << "Verified Deep Copy : ";
        printlist(copy);
        //printlist(head);
    }
    return 0;
}