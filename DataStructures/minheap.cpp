#include<bits/stdc++.h>
using namespace std;

//Min heap : element which is minimum will be the parent node
//Min heap property : parent node is less than it's both left and right child

class Minheap{
    private:
       int size;//size of heap
       int count;//number fo elements present in the heap
       int *arr;//array to store the elements of heap
    public:
       Minheap(){
           size = 100;
           count = 0;
           arr = new int[100];
       }
       Minheap(int size){
           this->size  = size;
           arr = new int[size];
           count = 0;
       }

      bool isFull(){
          return count == size;
      }
      
      bool empty(){
          return count == 0;
      }

      int parent(int node){
          if(node <=0 && node  >= count) return -1;
          return (node-1)>>1;
      }

      int left(int node){
          int l = 2*node+1;
          return l>=count?-1:l;
      }

      int right(int node){
         int r = 2*node+2;
         return r>=count?-1:r;
      }


      int gettop()
      {
          return empty()?-1:arr[0];
      }

      void prelocatedown(int i){
          int min = i;
          int l = left(i);
          int r = right(i);
          if(l!=-1 && arr[l] < arr[min]){
              min = l;
          }
          if(r!=-1 && arr[r] < arr[min]){
              min = r;
          }
          if(min!=i){
              swap(arr[min],arr[i]);
              prelocatedown(min);
          }
      }

      int deletetop(){
          if(empty()) return -1;
          int data = arr[0];
          arr[0] = arr[count-1];
          count--;
          prelocatedown(0);
          return data;
      }

      void resize(){
          int *a = arr;
          arr = new int[size*2];
          for(int i = 0;i<count;++i){
              arr[i] = a[i];
          }
        
          size*=2;
          delete(a);
      }

      void insert(int data){
          if(isFull()){
              resize();
          }
          count++;
          int i = count-1;
          while(i > 0 && arr[(i-1)>>1] > data){
                arr[i] = arr[(i-1)>>1];
                i = (i-1)>>1;
          }
          arr[i] = data;
      }


     void buildheap(int *a,int n){
          while(n > size){
              resize();
          }

          for(int i = 0;i<n;i++)
            arr[i] = a[i];
          count = n;

          for(int i = (n-1)/2; i>=0;i--){
              prelocatedown(i);
          }
      }

     void heapsort(int *a,int n){
        buildheap(a,n);
        
        for(int i = n-1;i>=0;i--){
            a[i] = arr[0];
            arr[0] = arr[count-1];
            --count;
            prelocatedown(0);
        }

      }

};



int main(){
    int n = 10;
    Minheap h(n);
    int arr[] = {1,2,3,5,4,3,-31,0};
    n = sizeof(arr)/sizeof(arr[0]);
    h.heapsort(arr,n);
    for(int i= 0;i<n;i++){
        cout<<arr[i]<<" ";
    }cout<<"\n";
    return 0;

}