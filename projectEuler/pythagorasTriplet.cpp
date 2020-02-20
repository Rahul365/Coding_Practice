// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

// a2 + b2 = c2
// For example, 32 + 42 = 9 + 16 = 25 = 52.

// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.

#include<bits/stdc++.h>
using namespace std;

int pow(int x,int y){
    int r = 1;
    while(y!=0){
        if(y&1) r = r*x;
        y = y>>1;
        x *= x;
    }
    return r;
}

bool checktriplet(int a,int b,int c){
    int m = max(a,max(b,c));
    if(c == m)
        return pow(m,2) == pow(a,2) + pow(b,2);
    if(b == m)
        return pow(m,2) == pow(a,2) + pow(c,2);
    return pow(m,2) == pow(b,2) + pow(c,2);
}

void findtriplet(){
    for(int i =1;i<=1000;i++){
        for(int j = 1;j<=1000;j++)
        {
                int k = 1000 - (i+j);  
                if(checktriplet(i,j,k)){
                    cout<<i<<" "<<j<<" "<<k<<"\n";
                    return;
                }
            }
        }
}

void findtripletII(){
    int a = 0;
    int b = 0;
    int c = 0;
    double m = 1;
    double n = 0;
    for(m=1;m*(m+n)!=500;++m)
     {
         bool found = false;
        for(n = m-1;n>=1;--n)
        {
            double val = m*(m+n);
            if(val == 500)
            {
                found = true;
                break;
            }
            
        }
        if(found) break;
     }
    cout<<m<<" "<<n<<"\n";
    a = 2*m*n;
    b = pow(m,2)-pow(n,2);
    c = pow(m,2)+pow(n,2);
    cout<<a<<" "<<b<<" "<<c<<"\n";
}

int main(){
    findtriplet();
    findtripletII();

    return 0;
}