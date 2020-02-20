#include<bits/stdc++.h>
using namespace std;


void print(vector<int> &prime){
    for(int p : prime){
        cout<<p<<" ";
    }
    cout<<"\n";
}

void simpleseive(int n,vector<int> &prime){
    vector<bool> mark(n+1,true);
    for(int i = 2;i<=n;i++){
        if(mark[i]){
            prime.push_back(i);
            for(int j = i*2;j<=n;j+=i){
                mark[j] = false;
            }
        }
    }
}


void segmentedseive(int N){
    cout<<"Prime numbers upto "<<N<<" are : ";
    int limit = ceil(sqrt(N));
    vector<int> prime;
    simpleseive(limit,prime);

    int low = limit;
    int high = 2*limit;
    while(low < N){
        high = min(high,N);
        vector<bool> mark(limit+1,true);

        for(int p : prime){
            int lowlim = floor(low/p)*p;
            if(lowlim < low) lowlim+=p;
            for(int i = lowlim;i<high;i+=p){
               mark[i-low] = false;
            }
        }

        for(int i = low;i<high;i++)
            if(mark[i-low]) prime.push_back(i);

        low += limit;
        high += limit;
    }

    print(prime);

}
int main(){
    segmentedseive(1000);
    return 0;
}