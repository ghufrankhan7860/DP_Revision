//  Longest Increasing Subsequence
// Problem statement
// For a given array with N elements, you need to find the length of the longest subsequence from the array such that all the elements of the subsequence are sorted in strictly increasing order.
// Strictly Increasing Sequence is when each term in the sequence is larger than the preceding term.
// For example:
// [1, 2, 3, 4] is a strictly increasing array, while [2, 1, 4, 3] is not.
// Sample Input :
// 6
// 5 4 11 1 16 8
// Sample Output 1 :
// 3
// Explanation of Sample Input 1:
// Length of longest subsequence is 3 i.e. [5, 11, 16] or [4, 11, 16].

#include <bits/stdc++.h>
using namespace std;

// recursive solution
int solve1(int arr[], int n, int last, int idx){
    if(idx>=n)  return 0;

    int take = 0, skip =0 ;
    if(last==-1 || arr[idx] > arr[last]){
        take = 1 + solve1(arr, n, idx, idx+1);
    }
    skip = solve1(arr, n, last, idx+1);
    return max(take, skip);
}

// memoization solution
int dp[1001][1001];
int solve2(int arr[], int n, int last, int idx){
    if(idx>=n)  return 0;

    if(last != -1 && dp[last][idx] != -1)   return dp[last][idx];

    int take = 0, skip =0 ;
    if(last==-1 || arr[idx] > arr[last]){
        take = 1 + solve2(arr, n, idx, idx+1);
    }
    skip = solve2(arr, n, last, idx+1);
    if(last == -1)  return max(take, skip);
    return dp[last][idx] =  max(take, skip);
}

// bottom up solution
int solve3(int arr[], int n){
    vector<vector<int>> dp(n+2, vector<int> (n+1, 0));

    for(int idx=n-1; idx>=0; idx--){
        for(int last=idx-1; last>=-1; last--){
            int take = 0, skip =0 ;
            if(last==-1 || arr[idx] > arr[last]){
                take = 1 + dp[idx+1][idx+1];
            }
            skip =  dp[last+1][idx+1];
            
            dp[last+1][idx] =  max(take, skip);
        }
    }
    return dp[0][0];

}

// bottom up solution->space optimisation
int solve4(int arr[], int n){
    vector<int> prev(n+1, 0), curr(n+1, 0);

    for(int idx=n-1; idx>=0; idx--){
        for(int last=idx-1; last>=-1; last--){
            int take = 0, skip =0 ;
            if(last==-1 || arr[idx] > arr[last]){
                take = 1 + prev[idx+1];
            }
            skip =  prev[last+1];
            
            curr[last+1] =  max(take, skip);
        }
        prev=curr;
    }
    return prev[0];

}

// non intutitive approach
int solve(int arr[], int n){
    vector<int> dp(n,1);

    int maxlen=1;
    for(int i=1; i<n; i++){
        for(int j=0; j<i; j++){
            if(arr[i] > arr[j]  && dp[j]+1>dp[i]){
                dp[i] = dp[j] +1;
                if(dp[i] > maxlen)  maxlen=dp[i];
            }
        }
    }
    return maxlen;
}

// using binary search and most effective sol
int LISlen(int arr[], int n){
    vector<int> dp;
    dp.push_back(arr[0]);
    int len=1;

    for(int i=1; i<n; i++){
        if(dp.back() < arr[i]){
            dp.push_back(arr[i]);
            len++;
        }
        else{
            int idx= lower_bound(dp.begin(), dp.end(), arr[i])-dp.begin();
            dp[idx] = arr[i];
        }
    }
    return len;
}

int longestIncreasingSubsequence(int arr[], int n)
{
    // // recursive sol
    // return solve1(arr, n, -1, 0);
    
    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(arr, n, -1, 0);
    
    // // bottomup sol
    // return solve3(arr, n);
   
    // // bottomup sol- >spcae optimisation
    // return solve4(arr, n);
    
    // // tabulation sol -> non intuitive
    // return solve(arr, n);
    
    // using binary search -> non intuitive
    return LISlen(arr, n);
}

int main(){
    vector<int> nums = {5,4,11,1,16,8};
    int n=nums.size();
    int *arr=new int[n];
    for(int i=0; i<n; i++)  arr[i] = nums[i];
    cout<<longestIncreasingSubsequence(arr, n)<<endl;
    return 0;
}