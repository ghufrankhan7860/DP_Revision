// Problem statement
// You are given an array 'arr' of 'n' integers.
// You have to divide the array into some subarrays such that each element is present in exactly one of the subarrays.
// The length of each subarray should be at most 'k'. After partitioning all the elements of each subarray will be changed to the maximum element present in that subarray.
// Find the maximum possible sum of all the elements after partitioning.
// Note:
// Input is given such that the answer will fit in a 32-bit integer.
// Example:
// Input: 'k' = 3, 'arr' = [1, 20, 13, 4, 4, 1]
// Output: 80

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(vector<int> &arr, int idx, int k){
    if(idx==arr.size())  return 0;

    int maxSum = 0, maxe = arr[idx];

    for(int i=idx; i<arr.size() && i<idx+k ; i++){
        maxe=max(maxe, arr[i]);
        maxSum = max(maxSum, (i-idx+1)*maxe + solve1(arr, i+1, k));
    }
    return maxSum;
}

// memoization sol
int dp[300];
int solve2(vector<int> &arr, int idx, int k){
    if(idx==arr.size())  return 0;

    if(dp[idx] != -1)   return dp[idx];

    int maxSum = 0, maxe = arr[idx];

    for(int i=idx; i<arr.size() && i<idx+k ; i++){
        maxe=max(maxe, arr[i]);
        maxSum = max(maxSum, (i-idx+1)*maxe + solve2(arr, i+1, k));
    }
    return dp[idx] = maxSum;
}

// bottom up 
int solve3(vector<int> &arr, int k){
    int n=arr.size();
    vector<int> dp(n+1, 0);

    for(int idx= n-1; idx>=0; idx--){
        int maxSum=0, maxe=0;
        for(int i=idx; i<n && i<idx+k; i++){
            maxe = max(maxe, arr[i]);
            maxSum = max(maxSum, (i-idx+1)*maxe + dp[i+1]);
        }
        dp[idx] = maxSum;
    }
    return dp[0];
}


int maximumSubarray(vector<int> &arr, int k){
    // // recursive sol
    // return solve1(arr, 0, k);
    
    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(arr, 0, k);

    // bottom up
    return solve3(arr, k);
}

int main(){
    vector<int> arr= {1,15,7,9,2,5,10};
    int n=arr.size();
    int k=3;
    cout<<maximumSubarray(arr, k)<<endl;
    return 0;
}