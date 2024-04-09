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

    // // bottomup dp solution
    // return solve3(s1, s2);

    // bottomup dp->space optimisation solution
    return solve4(s1, s2);
}

int main(){
    string s1="tjlyk";
    string s2="jlzy";
    cout<<canYouMake(s1, s2)<<endl;
    return 0;
}