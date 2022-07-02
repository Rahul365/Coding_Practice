#include<bits/stdc++.h>
using namespace std;

/**
 * Given an array nums of n integers, 
 * are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */


vector<vector<int>> findtriplets(vector<int> &a){
    vector<vector<int>> ans;
    if(a.size() < 3)
        return ans;
    int n = a.size();

    sort(a.begin(),a.end());

    for(int i = 0;i<n;i++){
        if(i > 0 && a[i] == a[i-1]) // this value has already been processed hence avoid this duplicate
            continue;
        int l = i+1;
        int r = n-1;
        while(l < r){
            int sum = a[i]  + a[l] + a[r];
            if(sum == 0){
                ans.push_back({a[i],a[l],a[r]});

                while(l < r && a[l] == a[l+1]){
                    l++;
                }

                while(l < r && a[r] == a[r-1]){
                    r--;
                }
                l++,r--;
            }
            else if(sum < 0){
                l++;
            }
            else{
                r--;
            }
        }
    }

    return ans;
}

int main(){
    vector<int> a;
    int n = 6;
    while(n--){
        int val;
        cin>>val;
        a.push_back(val);
    }
    vector<vector<int>> result = findtriplets(a);

    for(vector<int> v : result){
        for(int val : v){
            cout<<val <<" ";
        }cout<<"\n";
    }
    return 0;
}