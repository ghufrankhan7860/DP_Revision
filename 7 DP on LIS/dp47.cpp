//  Number of Longest Increasing Subsequence
// Problem statement
// Given an integer array ‘arr’ of length ‘n’, return the number of longest increasing subsequences in it.
// The longest increasing subsequence(LIS) is the longest subsequence of the given sequence such that all subsequent elements are in strictly increasing order.
// Example
// Input: ‘n’ = 5, ‘arr’ = [50, 3, 90, 60, 80].
// Output: 2

#include <bits/stdc++.h>
using namespace std;

//bottom up sol
int solve(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n, 1), countLIS(n, 1);
    
    int maxlen=1, last=0;
    for(int i=1; i<n; i++){
        for(int j=0; j<i; j++){
            if(arr[i] > arr[j]){
                if(dp[i] < dp[j] + 1){
                    dp[i] = dp[j] + 1;
                    if(dp[i] > maxlen){
                        maxlen = dp[i];
                        last = i;
                        countLIS[i] = countLIS[j];
                    }
                }
                else if(dp[i] == dp[j] + 1){
                    countLIS[i] += countLIS[j];
                }
            }
        }
    }
    
    for(auto it:dp) cout<<it<<" ";
    cout<<endl;
    for(auto it:countLIS)   cout<<it<<" ";
    cout<<endl;

    int noOfLIS= 0;
    for(int i=0; i<n; i++){
        if(dp[i] == maxlen){
            noOfLIS += countLIS[i];
        }
    }
    return noOfLIS;
}

int findNumberOfLIS(vector<int> &arr)
{
    return solve(arr);
}
int main(){
    vector<int> arr={50, 3, 90, 60, 80};
    cout<< findNumberOfLIS(arr)<<endl;
    return 0;
}