/**
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include<bits/stdc++.h>
using namespace std;

int smallestMultipleDivisibleFromLtoR(int l,int r){
    for(int i = 100;;i++){
        bool alldiv = true;
        for(int j = l;j<=r;j++){
            if(i%j!=0){
                alldiv = false;
                break;
            }
        }
        if(alldiv){
            return i;
        }
    }
    return -1;
}

int main(){
    cout<<smallestMultipleDivisibleFromLtoR(1,10)<<"\n";
    cout<<smallestMultipleDivisibleFromLtoR(1,20)<<"\n";
    return 0;
}