//  Subset Sum Equal To K
// Problem statement
// You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.
// Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.
// For Example :
// If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.
// Sample Input 1:
// 2
// 4 5
// 4 3 2 1
// 5 4
// 2 5 1 6 7
// Sample Output 1:
// true
// false

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(int n, int idx, int k, vector<int> &arr){
    if(k==0)    return 1;

    if(idx >= n)  return 0;

    int take = 0, skip = 0;

    if(arr[idx] <= k){
        take = solve1(n, idx+1, k-arr[idx], arr);
    }

    skip = solve1(n, idx+1, k, arr);
    
    return  take || skip;
}

// memoization sol
int dp[1001][1001];
int solve2(int n, int idx, int k, vector<int> &arr){
    if(k==0)    return 1;

    if(idx >= n)  return 0;

    if(dp[idx][k] != -1)    return dp[idx][k];

    int take = 0, skip = 0;

    if(arr[idx] <= k){
        take = solve2(n, idx+1, k-arr[idx], arr);
    }

    skip = solve2(n, idx+1, k, arr);
    
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

bool subsetSumToK(int n, int k, vector<int> &arr) {

    // // recursive solution
    // if(solve1(n, 0, k, arr)) return true;
    // return false;

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // if(solve2(n, 0, k, arr)) return true;
    // return false;


    // // bottom up
    // if(solve3(n, k, arr)) return true;
    // return false;


    // bottom up->space optimisation
    if(solve4(n, k, arr)) return true;
    return false;
}

int main(){
    vector<int> nums= {1,3};
    int k = 2;
    int n=nums.size();
    cout<<subsetSumToK(n, k, nums)<<endl;
    return 0;
}