#include<bits/stdc++.h>
using namespace std;
/*represents the linked list node*/
class Node{
    public:
     int data;
     Node *next;
     Node(int data){
         this->data =data;
         next = NULL;
     }
};
/*represents the head pointer for each vertex*/
class adjNode{
    public:
     Node *head;  
};

/*represent the adjNode list of V vertices*/
class List{
    private: 
        adjNode *list = NULL;
        int V;
        int E;
    public:
        List(int V,int E){
            list = new adjNode[V];//create a list of V vertices
            this->V = V;
            this->E = E;
            //initialize head pointers for V vertices
            for(int i = 0;i<V;i++){
                list[i].head = NULL;
            }
        }
        //add bidirectional edges
        void addEdgebi(int u,int v){
            Node *newnode = new Node(v);
            newnode->next = list[u].head;
            list[u].head = newnode;

            newnode = new Node(u);
            newnode->next = list[v].head;
            list[v].head = newnode;
        }

        void printall(){
            for(int i= 0;i<V;i++){
                printlistof(i);
            }
        }

        void printlistof(int node){
            Node *headref = list[node].head;
            cout<<"List of node : "<<node<<"\n";
            while(headref){
                cout<<headref->data<<" ";
                headref = headref->next;
            }
            cout<<"\n";
        }
};


int main(){
    int n = 5;
    List list(n,n-1);
    list.addEdgebi(0,1);
    list.addEdgebi(0,2);
    list.addEdgebi(0,3);
    list.addEdgebi(0,4);
    list.addEdgebi(4,2);
    list.addEdgebi(4,3);
    list.printall();
    return 0;
}