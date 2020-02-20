#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    double median(const vector<int>& A,const vector<int>& B,const int &n,const int &m){
     int s = 1;
     int e = n;
      //len(A) > len(B)
     int i = (s+e)>>1;//take the middle of A[0..(n-1)]
     int f = (n + m + 1)>>1;//mid of total => factor of partition
     int j = f-i;//gives the index of element int B[] such that NA + NB ==(t - NA-NB)
     //where  NA = NumberofElements(A[0..i-1]),NB = NumberofElements(B[0..j-1])
     while(s <= e){
         if((i>0 && j<m) && (A[i-1] > B[j])){//too much on right of A
         //move towards left of A
             e = i-1;
         }
         else if((j>0 && i < n )&& (B[j-1] > A[i])){//too much on left of A
             s = i+1;//move towards right of A
         }
         else{
             //partition indexes found 
             //such that A[i-1] <= B[j] and B[j-1] <= A[i]
             break;
         }
         i = (s+e)>>1;//compute the next point of partition
         j = f-i;
     }
    //compute the median and return
     int maxA = (i>0)?A[i-1]:INT_MIN;
     int maxB = (j>0)?B[j-1]:INT_MIN;
     int minA = (i<n)?A[i]:INT_MAX;
     int minB = (j<m)?B[j]:INT_MAX;
    
        if((n+m)&1){
            return (double)max(maxA,maxB);
        }
        else{
            return (double)(max(maxA,maxB)+min(minA,minB))/(double)2;
        }
        
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
       int n = nums1.size();
       int m = nums2.size();
       if(n > m)
           return median(nums2,nums1,m,n);
       else
           return median(nums1,nums2,n,m);
    }
};