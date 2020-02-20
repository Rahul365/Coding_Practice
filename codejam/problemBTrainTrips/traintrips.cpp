#include<bits/stdc++.h>
using namespace std;
/**
 * https://code.google.com/codejam/contest/32013/dashboard#s=p1
 * Problem B - Train Timetable
*/
int partition(vector<int> &a,int l,int r){
    int i = l+1;
    int j = r;
    int piv = a[l];
    while(i <= j){
       while(a[i] <= piv) ++i;
       while(a[j] > piv) --j;
       if(i < j)
        swap(a[i],a[j]);
    }
    swap(a[l],a[j]);
    return j;
}

void quicksort(vector<int> &a,int l,int r){
    if(l < r){
        int pid  = partition(a,l,r);
        quicksort(a,l,pid-1);
        quicksort(a,pid+1,r);
    }
}

void solve(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int cases;//number of test cases
    cin>>cases;
    for(int c = 1;c<=cases;++c){
        int tt,na,nb;
        cin>>tt>>na>>nb;
        int dh,dm,ah,am;
        vector<int> departfromA,readyAtB,departfromB,readyAtA;
        for(int i = 0;i<na;i++){
            cin>>dh; getchar(); cin>>dm;
            cin>>ah; getchar(); cin>>am;
            departfromA.push_back(dh*60 + dm);
            readyAtB.push_back(ah*60 + am + tt);
        }

        for(int i = 0;i<nb;++i){
            cin>>dh; getchar(); cin>>dm;
            cin>>ah; getchar(); cin>>am;
            departfromB.push_back(dh*60 + dm);
            readyAtA.push_back(ah*60 + am + tt);
        }
        //sort all the recording times in ascending order
        quicksort(departfromA,0,na-1);
        quicksort(readyAtB,0,na-1);
        quicksort(departfromB,0,nb-1);
        quicksort(readyAtA,0,nb-1);
        
        int i = 0;
        int j = 0;
        int fromA = 0;
        int fromB = 0;
        while(i < na){
            if(j < nb && departfromA[i] >= readyAtA[j]){
                j++;
            }
            else{
                fromA++;
            }
            ++i;
        }

        i = 0,j = 0;
        while(i < nb){
            if(j < na && departfromB[i] >= readyAtB[j]){
                j++;
            }
            else{
                fromB++;
            }
            ++i;
        }
        cout<<"Case #"<<c<<": "<<fromA<<" "<<fromB<<"\n";
    }
}

int main(){
    solve();
    return 0;
}