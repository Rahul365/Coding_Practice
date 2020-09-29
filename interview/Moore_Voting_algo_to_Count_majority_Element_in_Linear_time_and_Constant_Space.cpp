#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    inline int findCandidate(const vector<int> &nums,const int &to_exclude_1,const int &to_exclude_2,const int &to_exclude_3,const int &to_exclude_4){
        const int n = nums.size();
        int maj_index = -1;
        int count = 0;
        for(int i = 0;i<n;++i){
            if(to_exclude_1 == nums[i] || to_exclude_2 == nums[i] || to_exclude_3 == nums[i] || to_exclude_4 == nums[i]) continue;
            //if this condition is not involved here then we need at least 4 runs of these algorithm
            //i.e. (8 * n) is the time complexity
            //But just to improve the complexity for best cases , we can put this condition here to save some time
            if(count > nums.size()/3) return maj_index;
            if(maj_index!=-1){
                if(nums[maj_index] == nums[i]){
                    ++count;
                }
                else{
                    --count;
                }
            }
            
            if(maj_index == -1 || count == 0){
                maj_index = i;
                count = 1;
            }
        }
        return maj_index;
    }
    
    inline int isMajority(const vector<int> &nums,const int candidate){
        int count = 0;
        for(int v : nums){
            count += v == candidate;
        }
        return count > nums.size()/3;
    }
    
    vector<int> majorityElement(const vector<int>& nums) {
       const int n = nums.size();
       vector<int> answer;
       int to_exclude_1 = INT_MIN;//none 
       int to_exclude_2 = INT_MIN;
       int to_exclude_3 = INT_MIN;
       int to_exclude_4 = INT_MIN;
       int candidate = findCandidate(nums,to_exclude_1,to_exclude_2,to_exclude_3,to_exclude_4);
       if(candidate == -1) return answer;
       if(isMajority(nums,nums[candidate])) answer.push_back(nums[candidate]);
        
       to_exclude_1  = nums[candidate];//none
       candidate = findCandidate(nums,to_exclude_1,to_exclude_2,to_exclude_3,to_exclude_4);
       if(candidate == -1) return answer;
       if(isMajority(nums,nums[candidate])) answer.push_back(nums[candidate]);
        
       to_exclude_2 = nums[candidate];//none
       candidate = findCandidate(nums,to_exclude_1,to_exclude_2,to_exclude_3,to_exclude_4);
       if(candidate == -1) return answer;
       if(isMajority(nums,nums[candidate])) answer.push_back(nums[candidate]);
       
       to_exclude_3 = nums[candidate];//none
       candidate = findCandidate(nums,to_exclude_1,to_exclude_2,to_exclude_3,to_exclude_4);
       if(candidate == -1) return answer;
       if(isMajority(nums,nums[candidate])) answer.push_back(nums[candidate]);
       
       to_exclude_4 = nums[candidate];//none
       candidate = findCandidate(nums,to_exclude_1,to_exclude_2,to_exclude_3,to_exclude_4);
       if(candidate == -1) return answer;
       if(isMajority(nums,nums[candidate])) answer.push_back(nums[candidate]);
       
       
       return answer;
    }
};


int main(){
    vector<int> nums({1,1,1,2,3,4,5,6});
    for(int v : Solution().majorityElement(nums)){
        cout << v <<" ";
    }
    cout <<"\n";
    return 0;
}