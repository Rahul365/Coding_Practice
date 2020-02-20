#include<bits/stdc++.h>
using namespace std;

bool compare(pair<int,int> p1,pair<int,int> p2){
    if(p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}


/**
 * return -1 if a is on left of b
 *         1 if a is on right of b
 *         -2 if a is intersecting or overlapping b
 */
int compareInterval(pair<int,int> a,pair<int,int> b){
    if(a.second < b.first)
    {
        return -1;
    }
    if(a.first  > b.second)
    {
        return 1;
    }
    
    return 0;
}

int main(){
    int n;
    cin>>n;
    vector<pair<int,int>> p;
    for(int i =0;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        p.push_back({x,y});
    }
    sort(p.begin(),p.end(),compare);

 for(int i = 0;i<n;i++){
     cout<<p[i].first<<" "<<p[i].second<<" | ";
 }
 cout<<"\n";

    int a,b;
    cin>>a>>b;
    if(a > b){
        swap(a,b);
    }
    pair<int,int> q = {a,b};
    int i = 0;
    int result = 0;
    int j = p.size()-1;
    while(i <= j){
        int mid = i + (j-i)/2;
        // cout<<mid<<"\n";
        int check = compareInterval(q,p[mid]);
        if(check == -2){
            result = -2;
            break;
        }
        else if(check < 0){
            result = mid;
            j = mid-1;
        }
        else{
            result = mid;
            i = mid+1;
        }
    }
    cout<<result<<"\n";
    return 0;
}