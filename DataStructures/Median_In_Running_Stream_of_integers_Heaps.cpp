#include<bits/stdc++.h>
using namespace std;

class Heaps{
    private:
        int *a;
        int size;
        int count;
        bool type;//true for minheap and false for maxheap
    public:
        Heaps(){}
        Heaps(int size){
            type = false;//maxheap default
            this->size = size;
            a = new int[size];
            count = 0;
        }

        Heaps(int size,bool type){
            this->type = type;
            this->size = size;
            a = new int[size];
            count = 0;
        }

        int parent(int i){
            return (i<=0 && i>=count)?-1:((i-1)>>1);
        }

        int left(int i){
            int l = 2*i+1;
            return l>=count?-1:l;
        }

        int right(int i){
            int r = 2*i+2;
            return r>=count?-1:r;
        }

        void prelocatedown(int i){
            int l = left(i);
            int r = right(i);
            if(type == true){
                int min = i;
                if(l != -1 && a[l] < a[min]){
                    min = l;
                }
                if(r!=-1 && a[r] < a[min]){
                    min = r;
                }
                if(min!=i){
                    swap(a[i],a[min]);
                    prelocatedown(min);
                }
            }
            else{
                int max = i;
                if(l!=-1 && a[l] > a[max]){
                    max = l;
                }
                if(r!=-1 && a[r] > a[max]){
                    max = r;
                }
                if(max!=i){
                    swap(a[i],a[max]);
                    prelocatedown(max);
                }
            }
        }

        bool full(){
            return count == size;
        }
        
        bool empty(){
            return count == 0;
        }

        int getTop(){
            if(empty()) return -1;
            return a[0];
        }

        int deleteTop(){
            if(empty()) return -1;
            int data = a[0];
            a[0] = a[count-1];
            count--;
            prelocatedown(0);
            return data;
        }


        void resizeheap(){
            int *temp = a;
            a = new int[size * 2];
            if(empty()){
                delete(temp);
                size*=2;
                return;
            }
            for(int i = 0;i<size;i++){
                a[i] = temp[i];
            }
            size*=2;
            delete(temp);
        }

        void insert(int data){
            if(full()) resizeheap();

            count++;
            int i = count-1;
            if(type){
                while(i > 0 && a[(i-1)>>1] > data){
                    a[i] = a[(i-1)>>1];
                    i = (i-1)>>1;
                }
                a[i] = data;
            }
            else{
                while(i > 0 && a[(i-1)>>1] < data){
                    a[i] = a[(i-1)>>1];
                    i = (i-1)>>1;
                }
                a[i] = data;
            }
        }


        void buildHeap(int *A,int n){
            while(size < n){
                resizeheap();
            }
            for(int i = 0;i<n;i++){
                a[i] = A[i];
            }
            count = n;
            for(int i = (n-1)>>1; i>=0;i--){
                prelocatedown(i);
            }
        }

        void heapsort(int *A,int n){
            buildHeap(A,n);
            
            int old_size = count;
            for(int i = n-1;i>=0;i++){
                A[i] = a[0];
                a[0] = a[count-1];
                count--;
                prelocatedown(0);
            }
        }

        int getcount(){
            return count;
        }
};



int main(){
    int n;
    cin>>n;
    int median = 0;
    int x;
    Heaps minheap(n,true);
    Heaps maxheap(n,false);
    for(int i = 0;i<n;i++){
        cin>>x;
        if(minheap.getcount() == maxheap.getcount()){
            if(x < median){
                maxheap.insert(x);
                median = maxheap.getTop();
            }
            else{
                minheap.insert(x);
                median = minheap.getTop();
            }
        }
        else if(maxheap.getcount() < minheap.getcount()){
                if(median < x){
                    maxheap.insert(minheap.deleteTop());
                    minheap.insert(x);
                }
                else{
                    maxheap.insert(x);
                }
            median = (maxheap.getTop() + minheap.getTop())>>1;
        }
        else{
            if(median > x){
                minheap.insert(maxheap.deleteTop());
                maxheap.insert(x);
            }
            else{
                minheap.insert(x);
            }
            median = (maxheap.getTop() + minheap.getTop())>>1;
        }
        cout<<median<<" ";
    }
    cout<<"\n";
    return 0;
}