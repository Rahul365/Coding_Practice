#include<bits/stdc++.h>
using namespace std;

class doSort{
    private :
    /**for quicksort**/
    int partition(int *a,int l,int r){
        int piv = a[l];
        int i = l+1;
        int j = r;
        while(i<=j){
            while(i<=j && a[i] <= piv)
                ++i;
            
            while(i<=j && piv < a[j])
                --j;
            if(i < j)
                swap(a[i],a[j]);
        }
        swap(a[l],a[j]);
        return j;
    }
    
    void quicksort(int *a,int l,int r){
        if(l < r){
        int piv = partition(a,l,r);
        quicksort(a,l,piv-1);
        quicksort(a,piv+1,r);
        }
    }
    /***quicksort ends here***/
    /***mergesort starts here***/
    void merge(int *a,int l,int m,int r){
        int *c = new int[r-l+1];
        int k = 0;
        int i = l,j = m+1;
        while(i <= m && j <= r)
        {
            if(a[i] <= a[j]){
                c[k++] = a[i++];
            }
            else if(a[i] > a[j]){
                c[k++] = a[j++];
            }
        }
        while(i <= m)
            c[k++] = a[i++];
        
        while(j<=r)
            c[k++] = a[j++];
        for(int i = 0;i<k;++i)
            a[l++] = c[i];
    }
    
    void mergesort(int *a,int l,int r){
        if(l < r){
            int m = l + (r-l)/2;
            mergesort(a,l,m);
            mergesort(a,m+1,r);
            merge(a,l,m,r);
        }
    }
    /***mergesort ends here***/
    
    
    /***countSort***/
    void countSort(int *a,int n){
        if(n <=0 ) return;
        int MAX = a[0];
        for(int i = 0;i<n;++i){
            MAX = max(a[i],MAX);
        }
        int cnt[MAX+1]; memset(cnt,0,sizeof cnt);
        for(int i = 0;i<n;++i)
            ++cnt[a[i]];
        for(int i = 1;i<=MAX;++i)
            cnt[i] += cnt[i-1];
        int *ans = new int [n];
        for(int i = 0;i<n;++i)
        {
            ans[cnt[a[i]]-1] = a[i]; 
            --cnt[a[i]];
        }
        for(int i = 0;i<n;++i)
            a[i] = ans[i];
        delete(ans);
    }
    /***countSort ends here***/
    
    
    /**radixSort***/
    void rcountSort(int *a,int n,int exp){
        int cnt[10];
        memset(cnt,0,sizeof cnt);
        for(int i = 0;i<n;++i){
            ++cnt[(a[i]/exp)%10];
        }
        for(int i = 1;i<10;++i)
            cnt[i] += cnt[i-1];
        
        int *b = new int[n];
        for(int i = n-1;i>=0;--i){
            b[cnt[(a[i]/exp)%10]-1] = a[i];
            --cnt[(a[i]/exp)%10];
        }
        for(int i= 0;i<n;++i)
            a[i] = b[i];
    }
    
    void radixSort(int *a,int n){
        int MAX = 0;
        for(int i= 0;i<n;++i) MAX = max(MAX,a[i]);
        int exp = 1;
        for(exp = 1;MAX/exp ;exp*=10)
            rcountSort(a,n,exp);
    }
    /***radixSort ends here***/
    public:
    doSort(){}
    
    void qSort(int *a,int n){
        quicksort(a,0,n-1);
    }
    
    void mSort(int *a,int n){
        mergesort(a,0,n-1);
    }
    
    void cSort(int *a,int n){
        countSort(a,n);
    }
    
    void rSort(int *a,int n){
        radixSort(a,n);
    }
};

void fillrandom(int *a,int n){
        for(int i = 0;i<n;++i)
            a[i] = rand()%31;
}

void print(int  *a,int n)
{
    for(int i = 0;i<n;++i)
        cout << a[i] << " " ;
    cout<<"\n";
}

int main(){
    srand(time(NULL));
    int n = 6;
    int a[n];
    doSort *help = new doSort();
    cout<<"QuickSort\n";
    fillrandom(a,n);
    
    print(a,n);
    help->qSort(a,n);
    print(a,n);
    
    cout<<"MergeSort\n";
    fillrandom(a,n);
    
    print(a,n);
    help->mSort(a,n);
    print(a,n);
    
    cout<<"CountSort\n";
    fillrandom(a,n);
    
    print(a,n);
    help->cSort(a,n);
    print(a,n);
    
    cout<<"RadixSort\n";
    fillrandom(a,n);
    
    print(a,n);
    help->rSort(a,n);
    print(a,n);
    
    return 0;
}
