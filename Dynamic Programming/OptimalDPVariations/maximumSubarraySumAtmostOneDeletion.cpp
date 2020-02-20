#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    /**
     * Given an array of n integers.
     * To find : maximum sum of contiguos subarray such that atmost one element is deleted from the sum
     * And subarray must have atleast one element in it after deletion(if that happens).
     *
     * 
     * Basic idea is taken from Kadane's algorithm
     * In kadane
     * we keep two states:
     *  maxsumsofar => maximum best sum of a contiguos subarray so far
     *  sumsofar => to store the sum of the contiguos subarray so far
     * Initially : 
     *  maxsumsofar = a[0];
     *  sumsofar = a[0];
     * Transitions are: 
     *  sumsofar = sumsofar + a[i];
     *  maxsumsofar = max(maxsumsofar, sumsofar)
     *  sumsofar = (sumsofar < 0 ? 0 : sumsofar)
     * 
     * In our problem ,we have to consider two states
     *  deleted => maximum subarray contiguos sum such that one element is deleted
     *  no_deleted => maximum subarray contiguos sum such that no element is deleted
     * Initially:
     *  deleted = 0;(a[0] is deleted)
     *  no_deleted = a[0];
     *  maxsum = a[0];
     * Transitions:
     *  deleted = max(deleted + a[i] , no_deleted(such that a[i] is the deleted element from subarray))
     *  no_deleted = max(no_deleted + a[i], a[i]);
     *  maxsum = max({deleted,no_delted,maxsum});
    */

    int deleted = 0;
    int no_deleted = a[0];
    int maxsum = a[0];
    for (int i = 1; i < n; i++)
    {
        deleted = max(deleted + a[i], no_deleted);
        no_deleted = max(no_deleted + a[i], a[i]);
        maxsum = max({maxsum, deleted, no_deleted});
    }

    printf("%d\n", maxsum);
    return 0;
}