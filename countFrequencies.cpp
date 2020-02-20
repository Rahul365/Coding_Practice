#include<bits/stdc++.h>
using namespace std;

/**
 * 1<=a[i]<=n
 */
int countFreq(int *a,int n){
    for(int i= 0;i<n;){
            if(a[i] <= 0)
            {
                i++;
                continue;
            }

            int elementIndex = a[i] - 1;


            if(a[elementIndex] > 0){
                a[i] = a[elementIndex];
                a[elementIndex] = -1;
            }
            else{
                a[elementIndex]--;
                a[i++] = 0;
            }      
    }

    for(int i = 0;i<n;i++){
        cout<<abs(a[i])<<"\n";
    }
    cout<<"\n";
}


void countfreqII(int *a,int n){
    for(int i  = 0;i<n;i++){
        a[i]--;
    }
    for(int i = 0;i<n;i++){
        a[a[i]%n] +=n;
    }

    for(int i = 0;i<n;i++){
        cout<<a[i]/n<<" ";
    }
    cout<<"\n";
}

int main(){
    return 0;
}