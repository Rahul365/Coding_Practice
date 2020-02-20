#include<bits/stdc++.h>
using namespace std;
const int N = 100;
int mat[N][N];

/**
 * Brute Force:
 * O(n^4) solution
 * Try every end_point for each start_point
*/
int maxSum(int R,int C){
    int maxSum = INT_MIN;
    int s_r = 0,s_c = 0;//top left corner (or start point)
    int e_r = 0,e_c = 0;//bottom right corner (or end point)
    for(int row = 0 ;row < R;++row){
        for(int col = 0;col < C;++col){
             int end_row = R-1;
             while(end_row >= row){
                 int end_col = C-1;
                 while(end_col >= col){
                    int sum  = 0;
                    for(int r = row;r <= end_row;r++)
                        for(int c = col;c <= end_col;c++)
                            sum += mat[r][c];

                    if(maxSum < sum){
                        s_r = row;
                        s_c = col;
                        e_r = end_row;
                        e_c = end_col;
                        maxSum = sum;
                    }
                    end_col--;
                 }
             end_row--;
             }
        }
    }
    cout<<"Top left : ("<<s_r<<","<<s_c<<")\n";
    cout<<"Top right : ("<<e_r<<","<<e_c<<")\n";
    return maxSum;
}

/**
 * To find the maximum sum and starting and ending row of the maximum contiguos sum
*/
int kadane(int *a,int *start_row,int *end_row,int R){
    int sum = 0;
    int maxsum = INT_MIN;
    int local_start = 0;
    *end_row = -1;//for case when all values are -ve in the array
    for(int i = 0;i<R;i++){
        sum += a[i];
        if(sum < 0){
            sum = 0;
            local_start = i+1;
        }
        else if(sum > maxsum){
            maxsum = sum;
            *start_row = local_start;
            *end_row = i;
        }
    }
    if(*end_row !=-1 )
        return maxsum;

    maxsum = a[0];
    *start_row = *end_row  = 0;
    for(int i = 1;i<R;i++){
        if(maxsum < a[i]){
            maxsum = a[i];
            *start_row = *end_row = i;
        }
    }
    return maxsum;
}

int maxSumII(int R,int C){
    int start_row = 0,start_col = 0;
    int end_row = 0,end_col = 0;
    int maxsum = INT_MIN;
    int temp[R];//to store the sum of each row from left to right column
    for(int left = 0;left < C;left++){
        memset(temp,0,sizeof(temp));
        for(int right = left;right < C;right++){
            for(int row = 0;row < R;row++){
                    temp[row] += mat[row][right];
            }

            int start = 0;
            int end = 0;
            int sum = kadane(temp,&start,&end,R);
            if(sum > maxsum){
                maxsum = sum;
                start_row = start;
                end_row = end;
                start_col = left;
                end_col = right;
            }
        }
    }
    cout<<"Top left : ("<<start_row<<","<<start_col<<")\n";
    cout<<"Bottom Right : ("<<end_row<<","<<end_col<<")\n";
    return maxsum;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        for(int i = 0 ;i<n;i++)
            for(int j  = 0 ;j<m;j++)
              cin>>mat[i][j];
        cout<<maxSum(n,m)<<"\n";
        cout<<maxSumII(n,m)<<"\n";

    }
    return 0;
}