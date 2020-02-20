#include<bits/stdc++.h>
using namespace std;

/**
 * Given three arrays , find and return intersection for these three arrays.
 * All the arrays are in sorted order.
 * All of them are equal in length.
*/
int findmin(int a,int b,int c){
    if(a < b || a < c) return 0;
    if(b < a || b < c) return 1;
    if(c < a || c < b) return 2;
    return 3;//all are equal
}

vector<int> findIntersection(vector<int> &a,vector<int> &b,vector<int> &c){
    vector<int> ans;
    int n = a.size();
    if(n == 0) return ans;
    int i = 0,j = 0,k =0;
    
    while(i<n && j<n && k<n){
        int minid = findmin(a[i],b[j],c[k]);
        if(minid == 0){//a[i] is minimum than both
            i++;
        }
        else if(minid == 1)//b[j] is minimum
        {
            j++;
        }
        else if(minid == 2)//c[k] is minimum
        {
            k++;
        }
        else{
            //all are same
            ans.push_back(a[i]);
            ++i,++j,++k;
        }
    }
    return ans;
}


int main(){
    int n = 6;
    vector<int> a{2,6,9,11,13,17};
    vector<int> b{3,6,7,10,13,18};
    vector<int> c{4,5,6,9,11,13};
    /**if duplicates are present in the array 
     * we can be asked to either include the duplicates or not 
     * if( not ){
     * while(index > 0 && arr[index-1] == arr[index]) index++;
     * }
    */
    vector<int> intersection = findIntersection(a,b,c);

    for(int x : intersection)
        cout<<x<<" ";
    cout<<"\n";
    return 0;
}