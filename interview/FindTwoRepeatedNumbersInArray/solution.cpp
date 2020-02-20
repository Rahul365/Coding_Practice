/**
 * Problem : Given an array of k elements
 * In this array all the elements are in range from 1 to n.
 * All the  number appears exactly once except two numbers.
 * Find and print those two numbers.
*/

/**
 * XOR property:
 * To find the rightmost set bit position a number X : 
 * use the formula:
 *  X = X & ~(X-1);
*/
#include<bits/stdc++.h>
using namespace std;

void findTwoRepeatedElements(int *a,int K){
    int n = K - 2;
    int XOR = 0;
    for(int i = 1;i<=n;i++)
        XOR^=i;
    
    for(int i = 0;i<K;i++)
        XOR^= a[i];

    //find the rightmost set bit
    int rm = XOR & ~(XOR-1);
    
    int x = 0;
    int y = 0;
    for(int i = 1;i<=n;i++){
        if(i & rm){
            x ^= i;
        }
        else
        {
            y ^=  i;
        }    
    }

    for(int i = 0;i<K;i++){
        if(a[i] & rm){
            x ^= a[i];
        }
        else
        {
            y ^= a[i];
        }
    }
    cout<<x<<" "<<y<<"\n";
}


int main(){
    int a[] = {1,2,3,5,4,6,8,7,8,9,5};
    int n = sizeof(a)/sizeof(a[0]);
    findTwoRepeatedElements(a,n);
    return 0;
}
