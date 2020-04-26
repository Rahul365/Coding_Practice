#include<bits/stdc++.h>
#define MAXN 100000
#define BLOCKS  10000
using namespace std;

template<typename T>
class sqrtDcmp{
    vector<T> d;//sqrt decomposition array
    vector<T> a;//original array
    int block_size;
    int block_count;
    public:
    sqrtDcmp(vector<T> _a){
        int n = _a.size();
        a = _a;
        block_size = sqrt(n);
        block_count = (n/block_size) +  (n%block_size !=0);
        d = vector<T>(block_count,0);
        for(int i= 0;i<n;++i){
            d[i/block_size]+=a[i];
        }
    }
    
    void update(int pos,T val){
        d[pos/block_size] += val - a[pos];
        a[pos] = val;
    }
    
    int sum(int l,int r){
        T res = 0;
        while(l <= r && l%block_size){
            res += a[l++];
        }
        while(l+block_size <= r){
            res += d[l/block_size];
            l+=block_size;
        }
        while(l <= r){
            res += a[l++];
        }
        return res;
    }
};

/**
 * Idea is to divide the array into blocks of size sqrt(n), where  n is the size of the array.
 * 
*/
int block[BLOCKS];
int arr[MAXN];
int block_size;//size of a block

//Time : O(1)
void update(int index,int val){
    int blockindex = index / block_size;
    block[blockindex] +=  (val-arr[index]);
    arr[index] = val;
}
//Time : O(sqrt(n))
int query(int l , int r){
    int sum = 0;
    while(l <= r && l%block_size!=0){
        //add values from the left block
        sum += arr[l++];
    }

    while(l + block_size <= r){
        sum += block[l/block_size];
        l+=block_size;
    }

    while(l <= r){
        sum += arr[l++];
    }
    return sum;
}

//Time : O(sqrt(n))
void preprocesss(int *input,int n){
    block_size = sqrt(n);
    int block_index = -1;//initializing the block index here

    for(int i = 0;i<n;i++){
        arr[i] = input[i];
        if(i%block_size == 0){
            block_index++;//move to the next block
        }
        block[block_index] += arr[i];
    }
}

int main(){
    int a[] = {1,1,1,1,1,1,1,1,1,1};
    int n = sizeof(a)/sizeof(a[0]);
    preprocesss(a,n);
    cout<<query(0,n-1)<<"\n";
    cout<<query(0,n-2)<<"\n";
    cout<<query(0,n-3)<<"\n";
    update(n/2,10);
    cout<<query(0,n-1)<<"\n";
    cout<<query(0,n-2)<<"\n";
    cout<<query(0,n-3)<<"\n";

    return 0;
}