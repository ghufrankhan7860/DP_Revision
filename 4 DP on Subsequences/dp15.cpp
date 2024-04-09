// Partition Equal Subset Sum
// Problem statement
// You are given an array 'ARR' of 'N' positive integers. Your task is to find if we can partition the given array into two subsets such that the sum of elements in both subsets is equal.
// For example, let’s say the given array is [2, 3, 3, 3, 4, 5], then the array can be partitioned as [2, 3, 5], and [3, 3, 4] with equal sum 10.
// Follow Up:
// Can you solve this using not more than O(S) extra space, where S is the sum of all elements of the given array?
// Sample Input 1:
// 2
// 6
// 3 1 1 2 2 1
// 5
// 5 6 5 11 6
// Sample Output 1:
// true
// false

#include <bits/stdc++.h>
using namespace std;


// recursive sol
int solve1(vector<int> &arr, int n, int idx, int k){
    if(k==0)    return 1;

    if(idx >= n)  return 0;

    int take = 0, skip = 0;

    if(arr[idx] <= k){
        take = solve1(arr, n, idx+1, k-arr[idx]);
    }

    skip = solve1(arr, n, idx+1, k);
    
    return  take || skip;
}

// memoization sol
int dp[101][10001];
int solve2(vector<int> &arr, int n, int idx, int k){
    if(k==0)    return 1;

    if(idx >= n)  return 0;

    if(dp[idx][k] != -1)    return dp[idx][k];

    int take = 0, skip = 0;

    if(arr[idx] <= k){
        take = solve2(arr, n, idx+1, k-arr[idx]);
    }

    skip = solve2(arr, n, idx+1, k);
    
    return dp[idx][k] = take || skip;
}

// bottom up solution
int solve3(int n, int tar, vector<int> &arr){
    vector<vector<int>> dp(n+1, vector<int>(tar+1, 0));

    // base case
    for(int i=0; i<=n; i++) dp[i][0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        for(int k=0; k<=tar; k++){
            
            int take = 0, skip = 0;

            if(arr[idx] <= k){
                take = dp[idx+1][k-arr[idx]];
            }

            skip = dp[idx+1][k];
            
            dp[idx][k] = take || skip;
        }
    }
    return dp[0][tar];
}

// bottom up solution->space optimisation
int solve4(int n, int tar, vector<int> &arr){
    vector<int> prev(tar+1, 0), curr(tar+1, 0);

    // base case
    prev[0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        curr[0]=1;
        for(int k=0; k<=tar; k++){
            
            int take = 0, skip = 0;

            if(arr[idx] <= k){
                take = prev[k-arr[idx]];
            }

            skip = prev[k];
            
            curr[k] = take || skip;
        }
        prev=curr;
    }
    return prev[tar];
}


bool canPartition(vector<int> &arr, int n)
{
    int arrSum = 0;
    for (int it : arr)
        arrSum += it;

    // // recursive sol
    // if(arrSum %2 ==0)	return solve1(arr, n, 0, arrSum/2);
    // return false;

    // memoization sol
    memset(dp, -1, sizeof(dp));
    if(arrSum %2 ==0)	return solve2(arr, n, 0, arrSum/2);
    return false;

    // // bottom up sol
    // if (arrSum % 2 == 0)
    //     return solve3(n, arrSum / 2, arr);
    // return false;

    // // bottom up sol->space optimisation 
    // if (arrSum % 2 == 0) return solve4(n, arrSum / 2, arr);
    // return false;
}

int main()
{
    vector<int> nums= {2, 3, 3, 3, 4, 5};
    int n=nums.size();
    cout<<canPartition(nums, n)<<endl;

    return 0;
}