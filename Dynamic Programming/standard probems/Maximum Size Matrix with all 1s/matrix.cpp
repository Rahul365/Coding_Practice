#include<bits/stdc++.h>
using namespace std;
const int N = 100;
int A[N][N];
/*To find the maximum Rectangle Area in histogram*/
int maxRectangleArea(int *A,int n){
    int maxArea  = 0;
    stack<int> stk;

    for(int i = 0;i<=n;i++){
        while(!stk.empty() && (i == n || A[stk.top()] > A[i])){\
            int height = A[stk.top()];
            stk.pop();
            int width = stk.empty()?i: i -stk.top()-1;
            maxArea = max(maxArea , height * width);
        }
       
       if(i < n)
        stk.push(i);
    }
    return maxArea;
}


int maxSizeSubMatrixWithAll1s(int m,int n){
    int maxSize = 0;
    //modify each row of the array and build histogram for each row
    for(int i =1 ; i<m;i++){
        for(int j = 0;j<n;j++){
            if(A[i][j])
                A[i][j] += A[i-1][j];
        }
    }


    for(int i = 0;i<m;i++){
        maxSize = max(maxSize , maxRectangleArea(A[i],n));
    }

    //regenerate the original array
    for(int i = m-1;i>0;i--){
        for(int j=0 ;j<n;j++){
            A[i][j] -= A[i-1][j];
        }
    }

    return maxSize;
}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int m,n;
    cin>>m>>n;
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            cin>>A[i][j];
        }
    }
    cout<<maxSizeSubMatrixWithAll1s(m,n)<<"\n";
    return  0;
}