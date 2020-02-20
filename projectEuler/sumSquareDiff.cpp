/**
 * The sum of the squares of the first ten natural numbers is,

    12 + 22 + ... + 102 = 385
    The square of the sum of the first ten natural numbers is,

    (1 + 2 + ... + 10)2 = 552 = 3025
    Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

    Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

/**
 * we know for sum of squares of first n numbers
 *  use the formula =>  { s2(n) = (n*(n+1)*(2*n + 1))/6 }
 * as for the square of sum of first n numbers
 *  we know how to compute the sum of first n terms 
 *  use the formula =>  { s1(n) = n*(n+1)/2 }
 * So difference = s2(n) - (s1(n)*s1(n))
*/
#include<bits/stdc++.h>
using namespace std;

int pow(int x,int  y){
    int result = 1;
    while(y>0){
        if(y&1){
            result *= x;
        }
        y = y>>1;
        x = x*x;
    }
    return result;
}

int main(){
    int n = 100;
    int s2 = (n*(n+1)*((2*n) + 1))/6;
    int s1 = (n*(n+1))/2;
    cout<<s2<<"\n";
    cout<<pow(s1,2)<<"\n";
    cout<<(pow(s1,2) - s2)<<"\n";
    return 0;
}