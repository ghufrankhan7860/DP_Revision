//  Minimum Number of Deletions and Insertions
// Problem statement
// You are given 2 non-empty strings 's1' and 's2' consisting of lowercase English alphabets only.
// In one operation you can do either of the following on 's1':
// (1) Remove a character from any position in 's1'.
// (2) Add a character to any position in 's1'.
// Find the minimum number of operations required to convert string 's1' into 's2'.
// Example:
// Input: 's1' = "abcd", 's2' = "anc"
// Output: 3
// Explanation:
// Here, 's1' = "abcd", 's2' = "anc".

#include <bits/stdc++.h>
using namespace std;

// recursive solution
int solve1(int i, int j, string &s1, string &s2){
    if(i>=s1.size()) return s2.size()-j;
    if(j>=s2.size()) return s1.size()-i;

    int del = 1e9, ins = 1e9;

    if(s1[i] != s2[j]){
        del = solve1(i+1, j, s1, s2);
        ins = solve1(i, j+1, s1, s2);
        return 1 + min(del, ins);
    }   
    return solve1(i+1, j+1, s1, s2);
}

// memoization solution
int dp[101][101];
int solve2(int i, int j, string &s1, string &s2){
    if(i>=s1.size()) return s2.size()-j;
    if(j>=s2.size()) return s1.size()-i;

    if(dp[i][j] != -1)  return dp[i][j];

    int del = 1e9, ins = 1e9;

    if(s1[i] != s2[j]){
        del = solve2(i+1, j, s1, s2);
        ins = solve2(i, j+1, s1, s2);
        return dp[i][j] = 1 + min(del, ins);
    }   
    return dp[i][j] = solve2(i+1, j+1, s1, s2);
}

// bottom up solution
int solve3(string &s1, string &s2){
    int m=s1.size(), n=s2.size();

    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

    // base cases
    for(int i=0; i<m; i++) dp[i][n] = m-i;
    for(int j=0; j<n; j++) dp[m][j] = n-j;

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s1[i]==s2[j])    dp[i][j] = dp[i+1][j+1];
            else{
                dp[i][j] = 1 + min(dp[i][j+1], dp[i+1][j]);
            }
        }
    }
    return dp[0][0];
}

// bottom up solution->space optimisation
int solve4(string &s1, string &s2){
    int m=s1.size(), n=s2.size();

    vector<int> prev(n+1, 0), curr(n+1, 0);

    // base cases
    for(int j=0; j<n; j++) prev[j] = n-j;

    for(int i=m-1; i>=0; i--){
        curr[n] = m-i; 
        for(int j=n-1; j>=0; j--){
            if(s1[i]==s2[j])    curr[j] = prev[j+1];
            else{
                curr[j] = 1 + min(curr[j+1], prev[j]);
            }
        }
        prev=curr;
    }
    return prev[0];
}

int canYouMake(string &s1, string &s2){

    // // recursive sol
    // return solve1(0, 0, s1, s2);

    // memoization sol
    memset(dp, -1, sizeof(dp));
    return solve2(0, 0, s1, s2);

    // // bottomup dp solution
    // return solve3(s1, s2);

    // // bottomup dp->space optimisation solution
    // return solve4(s1, s2);
}

int main(){
    string s1="abcd";
    string s2="anc";
    cout<<canYouMake(s1, s2)<<endl;
    return 0;
}