/**
 * Given an array nums of positive integers, 
 * return the longest possible length of an array prefix of nums, 
 * such that it is possible to remove exactly one element from this 
 * prefix so that every number that has appeared in it will have the same number of occurrences.
 * If after removing one element there are no remaining elements, 
 * it's still considered that every appeared number has the same number of ocurrences (0).
 * 
 * Input: nums = [2,2,1,1,5,3,3,5]
 * Output: 7
 * Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, 
 * if we remove nums[4]=5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
*/


#include<bits/stdc++.h>
using namespace std;


int maxequalfreq(vector<int> &nums){
    int n = nums.size();
    map<int,int> freq;//to store frequency of nums[i]
    map<int,int> freq_freq;//to store number of elements for the frequency = freq[nums[i]]

    int answer = 0;

    for(int i = 0;i<n;i++)
    {
        if(freq[nums[i]] > 0){
            //if the current element has appeared before in the array so far
            //then it's freq[nums[i]]  will change this time
            //so we need to remove that element from the frequency category of it's previous frequency i.e. freq[nums[i]]
            //e.g if 4 is current element
             //prev frequency freq[4] = 1 ( > 0)
             //it's updated freq will be 2 this time
             //but before that remove it from freq_freq[freq[4]]--
            if(--freq_freq[freq[nums[i]]] == 0){
                //while removing nums[i] from the freq[nums[i]] category 
                //if there was only nums[i] that falls under the category freq[nums[i]]
                //erase it from the map
                freq_freq.erase(freq[nums[i]]);
            }
        }

        ++freq[nums[i]];
        ++freq_freq[freq[nums[i]]];//put nums[i] into new frequency category
        bool flag = false;
        //freq_freq map must have two categories at a time
        //like some elements fall under freq_category A and some under freq_category B
        //more than that and it is not possible to find such a prefix for the array from 0 to i
        if((int) freq_freq.size() <= 2){
            pair<int,int> p = *freq_freq.begin();
            //pick the entry from the front since the map is sorted data structure
            //minimum freq category will be at front
            if((int) freq_freq.size() == 1){
                //if there is only one category
                //and frequency category is 1 or there is only 1 element under such frequency
                //e.g nums[] = {1,1,2,2,3,3}
                //category is 2 
                //removing any element won't give solution here
                //let's take another sample
                //nums[] = {1,2,3,4,5}
                //category is 1
                //remove any element will meet the condition here
                //for (p.second == 1) case indicates there is only 1 elements under frequency category > 1 
                //nums[] = {5,5,5}
                //category 3 and number of elements under that is 1
                if(p.first == 1 || p.second == 1){
                    flag = true;
                }
            }
            else{
                //there will be two categories
                pair<int,int> q = *freq_freq.rbegin();
                //pick the last entry
                //nums[] = {8,2,2,3,3,4,4}
                if(p.first == 1 && p.second == 1){
                    //if the first category is 1 and elements under that category is also 1
                    //we have a solution
                    //_?_ indicates removed element 
                    //i.e nums[] ={_8_,2,2,3,3,4,4};
                    flag = true;
                }
                else if(p.first + 1 == q.first && q.second == 1){
                    //take nums[] = {1,1,1,2,2,2,3,3,3,4,4,4,3};
                    //two frequency Categories i.e. 3 and 4
                    //elements under 3 are : {1,2,4}
                    //elements under 4 are : {3}
                    //so firstcategoryFreq + 1 == secondcategoryFreq i.e 3 + 1 == 4
                    //and number of elements under second category == 1
                    //then we can get a solution by removing one element from the second category
                    //and then the element which was under category 4 will come under category 3
                    //nums[] = {1,1,1,2,2,2,3,3,3,4,4,4,_3_};
                    flag = true;
                }
            }
        }
        if(flag)
            answer = i + 1;
    }

    return answer;
}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> nums;
        int val;
        while(n--){
            cin>>val; nums.push_back(val);
        }
        cout<<maxequalfreq(nums)<<"\n";
    }
    return 0;
}