// //  Array partition with minimum difference
// Problem statement
// You are given an array 'arr' containing 'n' non-negative integers.
// Your task is to partition this array into two subsets such that the absolute difference between subset sums is minimum
// You just need to find the minimum absolute difference considering any valid division of the array elements.
// Note:
// 1. Each array element should belong to exactly one of the subsets.
// 2. Subsets need not always be contiguous.
// For example, for the array : [1, 2, 3], some of the possible divisions are 
//    a) {1,2} and {3}
//    b) {1,3} and {2}.
// 3. Subset-sum is the sum of all the elements in that subset. 
// Example:
// Input: 'n' = 5, 'arr' = [3, 1, 5, 2, 8].
// Ouput: 1
// Explanation: We can partition the given array into {3, 1, 5} and {2, 8}. 
// This will give us the minimum possible absolute difference i.e. (10 - 9 = 1).


#include <bits/stdc++.h>
using namespace std;


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

    int minDiff = 1e9;
    for(int i=tar/2; i<=tar; i++){
        if(dp[0][i]==1) {
            minDiff = min(minDiff, abs(i-(tar-i)));
        }
    }
    return minDiff;
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
    int minDiff = 1e9;
    for(int i=tar/2; i<=tar; i++){
        if(prev[i]==1) {
            minDiff = min(minDiff, abs(i-(tar-i)));
        }
    }
    return minDiff;
}

int minSubsetSumDifference(vector<int>& arr, int n)
{
    int tar = 0;
    for(auto it:arr)    tar += it;

	// bottom up solution
    return solve3(n, tar, arr);

	// bottom up solution->space optimisation
    return solve4(n, tar, arr);
    
}



int main(){
    vector<int> nums = {3, 1, 5, 2, 8 };
    int n=nums.size();
    cout<<minSubsetSumDifference(nums, n)<<endl;
    return 0;
}