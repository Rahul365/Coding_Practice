#include<bits/stdc++.h>
using namespace std;
/**
 * Find the max number of bridges  such that city[i].left can connect to city[i].right only.
 */
class city{
    public:
        int left;
        int right;
     city(){}
     city(int left,int right){
         this->left = left;
         this->right = right;
     }
};

/* check if a <= b*/
bool compare(city a,city b){
    if(a.left == b.left){
        return a.right <= b.right;
    }
    return a.left < b.left;
}

int partition(city *c, int l,int r){
    int i = l+1;
    int j = r;
    city piv = c[l];
    while(i<=j){
        while(i <= j && compare(c[i],piv)){
            //find the city from the left which is greater than piv_city
            i++;
        }
        while(i <= j && compare(piv,c[j])){
            //find the city from right which is less than piv_city
            j--;
        }

        if(i < j) swap(c[i],c[j]);
    }
    swap(c[l],c[j]);
    return j;
}

void quicksort(city *c,int l,int r){
    if(l <= r){
        int pid = partition(c,l,r);
        quicksort(c,l,pid-1);
        quicksort(c,pid+1,r);
    }
}


int maxbridges(city *c,int n){
    //1)sort the bridges according to the left side cities
    //for duplicate cities 
    //check if c[i].right <= c[j].right

    quicksort(c,0,n-1);
    // for(int i= 0;i<n;i++)
    // {
    //     cout<<c[i].left<<" ";
    // }
    //2) Now find the lis for the cities on the right side of river
    //3) Maximum of the LIS will be max number of bridges that can be formed

    int lis[n];
    int bc = 0;
    for(int i = 0;i<n;i++){
        lis[i] = 1;
        for(int j = 0;j<i;j++){
            if(c[i].right >= c[j].right && lis[i] < lis[j]+1){
                lis[i] = lis[j] + 1;
            }
        }
        bc = max(bc,lis[i]);
    }
    return bc;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int t;
    cin>>t;
    int c = 1;
    while(t--){
        cout<<"Case # "<<c++<<" : ";
        int n;//number of cities on sides of river
        cin>>n;
        city c[n];
        for(int i = 0;i<n;i++)
            cin>>c[i].left;//cities on left bank
        
        for(int i = 0;i<n;i++)
            cin>>c[i].right;//cities on right bank

        cout<<maxbridges(c,n)<<"\n";
    }
    return 0;
}