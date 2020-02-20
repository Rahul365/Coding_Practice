#include<bits/stdc++.h>
using namespace std;
/**
 * Given an array containing n elements (both positive,negative and zero values).
 * Find the maximum product value formed by contiguos subarray.
 * maxproduct could be any of (-inf-------0--------+inf)
 */
int maxproductsubarray(int *a,int n)
{
    int maxendinghere = 1;//max positive product value ending at current element
    int minendinghere = 1;//min negative product value ending at current element

    int maxsofar = 1;//maxproduct value so far;

    for(int i = 0;i<n;i++){
        if(a[i] > 0){//if the value is positive
        //max product value ending here would be maxendinghere * a[i]
        //ans minendinghere will min(minendinhere * a[i],1) 
            maxendinghere = maxendinghere * a[i];
            minendinghere = min(minendinghere * a[i],1);
        }
        else if(a[i] == 0){
            //if the current value is 0;
            //set the maxending here as 0 ending at current element for considering the zero product value also
            maxendinghere = 0;
            //minending here would be set to 1
            minendinghere = 1;
        }
        else{//if the current element is negative
        //maxending here  would be previous minendinghere *a[i]
        //and minending here would be previous maxending here  *a[i]
            int prevmaxending = maxendinghere;
            maxendinghere = minendinghere*a[i];//here we don't set maxending here to because a negative product value could also be considered as maximum
            minendinghere = prevmaxending*a[i];
        }
        //update the max product so far
        maxsofar = max(maxsofar,maxendinghere);
        //if the maxending here is less than or equal to 0
        //then maxendinghere must be set to 1 because max product value for the next subarrays can't be one
        if(maxendinghere <= 0)
            maxendinghere = 1;
    }
    return maxsofar;
}

int main(){
    int a[] = {-1,-2,0,-4,3,-3};
    int n = sizeof(a)/sizeof(a[0]);
    cout<<maxproductsubarray(a,n)<<"\n";
    return 0;
}