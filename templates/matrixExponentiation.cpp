#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int mod = 1e9+7;
const int N = 101;
int n,m,k;

//Matrix Exponentiation
template<typename T>
struct Matrix{
    T a[N][N] = {0};
    
    Matrix& operator *(const Matrix &other){
        Matrix product;
        for(int i = 0;i<(n);++i){
            for(int j = 0;j<(n);++j)
            {
                for(int k = 0;k<(n);++k){
                    product.a[i][j] += a[i][k]*other.a[k][j];
                    product.a[i][j] %= mod;
                }
            }
        }
        return (*this) = product;
    }

    Matrix& operator *= (const Matrix &other)
    {
        return (*this) * other;
    }

    void print(){
        for(int i = 0;i<n;++i){
            for(int j = 0;j<n;++j){
                cerr << a[i][j] << " \n"[j==1];
            }
        }
    }
};