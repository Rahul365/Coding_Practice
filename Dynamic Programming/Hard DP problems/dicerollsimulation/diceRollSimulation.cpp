/**
 * link : https://leetcode.com/problems/dice-roll-simulation/
 * A dice simulator can generate a random number from 1 to 6 for each roll.
 * Now if there is a restriction on number of times a number from 1 to 6 can appear consecutive times for multiple rolls of dice.
 * let that restriction be in the form of arrat rollMax[NUM], where 1<=NUM<=6
 * rollMAX[NUM] -> tells number of times a number can appear consecutively in sequence.
 * 
 * Given a value n , print the number of ways to generate a sequence of length n while keeping the
 * restrictions for each number in mind.
 * Since the answer could be very large use mod = 10^9 + 7
 */
#include<bits/stdc++.h>
using namespace std;


class Solution{
    const int mod = 1e9 + 7;
    void add_self(int &a,int b){
        a = (a + b)%mod;
    }

    public:
        int dicesimulations(int n,vector<int> rollMax){
            vector<vector<int>> ways(n+1,vector<int>(6));//ways to roll a dice to generate a sequence of length n
            //such that it ends with a number N from 1 to 6
            for(int num = 0;num < 6;++num){
                for(int len = 1;len <= min(n,rollMax[num]) ;++len)
                    ways[len][num]++;//roll number 'num' for 'len' number of times consecutively
            }

            for(int i = 1;i<n;i++){//start from sequence of length 1
                for(int prev = 0;prev < 6;prev++){//sequence ending with prev as prefix which appears upto i times
                    for(int next = 0;next < 6;++next){//fill the remaining sequence length with next as suffix
                        if(prev == next) continue;
                        //fill the remaining length of sequence with 'next' i.e i + len <= n
                        for(int len = 1;len <= rollMax[next] && i+len <= n;len++){
                            add_self(ways[i+len][next],ways[i][prev]);
                        }
                    }
                }
            }

            int ans = 0;
            for(int num = 0;num < 6;num++)
                add_self(ans,ways[n][num]);

            return ans;
        }
};


int main(){
    freopen("input_dice.txt","r",stdin);
    freopen("output_dice.txt","w",stdout);
    int t;
    cin>>t;
    vector<int> rollMax(6);
    while(t--){
        int n;//sequence length;
        cin>>n;
        
        for(int i = 0;i<6;i++){
            cin>>rollMax[i];
        }
        cout<<Solution().dicesimulations(n,rollMax)<<"\n";
    }
    return 0;
}