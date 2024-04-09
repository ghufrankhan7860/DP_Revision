// Problem statement
// You are given a string 'str' of length 'n'.
// Find the minimum number of partitions in the string so that no partition is empty and every partitioned substring is a palindrome.
// Example :
// Input: 'str' = "aaccb"
// Output: 2
// Explanation: We can make a valid partition like aa | cc | b. 

#include <bits/stdc++.h>
using namespace std;

bool isPalendrome(string &str, int i, int j){
    while(i<j){
        if(str[i] != str[j])    return false;
        i++; j--;
    }
    return true;
}


// recursive sol
int solve1(string &str, int idx, int n){

    if(idx==n)  return 0;

    int minCost = INT_MAX;
    for(int i=idx; i<n; i++){
        if(isPalendrome(str, idx, i))
            minCost = min(minCost, 1 + solve1(str, i+1, n));
    }
    return minCost;
}


// memoization sol
int dp[101];
int solve2(string &str, int idx, int n){

    if(idx==n)  return 0;

    if(dp[idx] != -1)   return dp[idx];
    int minCost = INT_MAX;
    for(int i=idx; i<n; i++){
        if(isPalendrome(str, idx, i))
            minCost = min(minCost, 1 + solve2(str, i+1, n));
    }
    return dp[idx] = minCost;
}

// bottom up solution
int solve3(string &str, int n){
    vector<int> dp(n+1, INT_MAX);
    dp[n]=0;

    for(int idx=n-1; idx>=0; idx--){
        int mini=1e9;
        for(int i=idx; i<n; i++){
            if(isPalendrome(str, idx, i)){
                mini = min(mini, 1 + dp[i+1]);
            }
        }
        dp[idx] = mini;
    }
    return dp[0];
}

int palindromePartitioning(string str)
{
    int n=str.size();
    // // recursive sol
    // return solve1(str, 0, n)-1;
   
    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(str, 0, n)-1;

    // bottom up 
    return solve3(str, n)-1;
}


int main(){
    string s = "aaccb";
    cout<<palindromePartitioning(s)<<endl;
    return 0;
}