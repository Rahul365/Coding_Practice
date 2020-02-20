#include <bits/stdc++.h>
using namespace std;
const int MAXX=1e6+2;
int cnt[MAXX];

/**
 * Given an array of n elements. find the maximum number of elements A[j] that are divisible by A[i]
 * such that j<i.
 */

/*Brute force*/
void solve(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    int a[n];
	    memset(cnt,0,sizeof(cnt));
	    for(int i =0;i<n;i++){
	        cin>>a[i];
	    }
	    
	    int max_val = 0;
	    int ans = 0;
	    for(int i=0;i<n;i++){
	        int count = 0;
	        if(a[i] == 1){
	            count = i;
	        }
	        else if(a[i] <= max_val){
	            for(int j = 1;j*a[i]<=max_val;j++){
	                if(cnt[a[i]*j]){
	                    count+=cnt[a[i]*j];
	                }
	            }
	        }
	        ans = max(ans,count);
	        cnt[a[i]]++;
	        max_val = max(a[i],max_val);
	    }
	    cout<<ans<<"\n";
	}	
}

/*O(n*sqrt(n))*/
void solveII(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    int a[n];
	    memset(cnt,-1,sizeof(cnt));
	    for(int i =0;i<n;i++){
	        cin>>a[i];
	    }
	    
	    for(int i = n-1;i>=0;i--){
	        if(a[i] == 1) continue;

	        for(int j =2;j<=sqrt(a[i]);j++){
	            if(a[i]%j == 0){
	                if(a[i]/j == j && cnt[j]>=0){
	                    cnt[j]++;
	                }
	                else{
						if(cnt[j] >= 0)
		                    cnt[j]++;
						if(cnt[a[i]/j] >= 0)
	                    cnt[a[i]/j]++;
	                }
	            }
	        }
	       
	          cnt[a[i]]++;
	    }

	    for(int i = 0;i<n;i++){
	        cout<<cnt[a[i]]<<" ";
	    }
	    cout<<"\n";
	    int ans = 0;
	    for(int i = 0;i<n;i++){
	        if(a[i] == 1){
	            ans = max(ans,a[i]);
	        }
	        else{
	            ans = max(ans,cnt[a[i]]);
	        }
	    }
	    
	    
	    cout<<ans<<"\n";
	}
}


int main(){
	return 0;
}