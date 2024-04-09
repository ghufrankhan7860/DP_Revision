//  Count Subsets with Sum K
// Problem statement
// You are given an array 'arr' of size 'n' containing positive integers and a target sum 'k'.
// Find the number of ways of selecting the elements from the array such that the sum of chosen elements is equal to the target 'k'.
// Since the number of ways can be very large, print it modulo 10 ^ 9 + 7.
// Example:
// Input: 'arr' = [1, 1, 4, 5] , k =5
// Output: 3
// Explanation: The possible ways are:
// [1, 4]
// [1, 4]
// [5]

#include <bits/stdc++.h>
using namespace std;

int mod = 1e9+7;

// recursive sol
long solve1(vector<int> &arr, int n, int idx, int k){
    if(k==0)    return 1;

    if(idx >= n)  return 0;

    long take = 0, skip = 0;

    if(arr[idx] <= k){
        take = solve1(arr, n, idx+1, k-arr[idx]);
    }

    skip = solve1(arr, n, idx+1, k);
    
    return  (take + skip)%mod;
}

// memoization sol
int dp[101][1001];
long solve2(vector<int> &arr, int n, int idx, int k){
    if(k==0)    return 1;

    if(idx >= n)  return 0;

    if(dp[idx][k] != -1)    return dp[idx][k];

    long take = 0, skip = 0;

    if(arr[idx] <= k){
        take = solve2(arr, n, idx+1, k-arr[idx]);
    }

    skip = solve2(arr, n, idx+1, k);
    
    return dp[idx][k] = (take + skip)%mod;
}

// bottom up solution
long solve3(int n, int tar, vector<int> &arr){
    vector<vector<int>> dp(n+1, vector<int>(tar+1, 0));

    // base case
    for(int i=0; i<=n; i++) dp[i][0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        for(int k=0; k<=tar; k++){
            
            long take = 0, skip = 0;

            if(arr[idx] <= k){
                take = dp[idx+1][k-arr[idx]];
            }

            skip = dp[idx+1][k];
            
            dp[idx][k] = (take + skip)%mod;
        }
    }
    return dp[0][tar];
}

// bottom up solution->space optimisation
long solve4(int n, int tar, vector<int> &arr){
    vector<int> prev(tar+1, 0), curr(tar+1, 0);

    // base case
    prev[0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        curr[0]=1;
        for(int k=0; k<=tar; k++){
            
            long take = 0, skip = 0;

            if(arr[idx] <= k){
                take = prev[k-arr[idx]];
            }

            skip = prev[k];
            
            curr[k] = (take + skip)%mod;
        }
        prev=curr;
    }
    return prev[tar];
}


int findWays(vector<int>& arr, int k)
{
    int n = arr.size();
    sort(arr.begin(), arr.end());
    // // recursive solution
    // return solve1(arr, arr.size(), 0, k);

    // memoization solution
    memset(dp, -1, sizeof(dp));
    return solve2(arr, arr.size(), 0, k);

    // // bottom up solution
    // return solve3(n, k, arr);

    // // bottom up solution->space optimisation
    // return solve4(n, k, arr);
}



int main(){
    vector<int> arr = {1, 1, 4, 5};

    int k = 5;
    cout<<findWays(arr, k)<<endl;
    return 0;
}