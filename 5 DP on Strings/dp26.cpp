//  Print Longest Common Subsequence
// Problem statement
// You are given two strings ‘s1’ and ‘s2’.
// Return the longest common subsequence of these strings.
// If there’s no such string, return an empty string. If there are multiple possible answers, return any such string.
// Note:
// Longest common subsequence of string ‘s1’ and ‘s2’ is the longest subsequence of ‘s1’ that is also a subsequence of ‘s2’. A ‘subsequence’ of ‘s1’ is a string that can be formed by deleting one or more (possibly zero) characters from ‘s1’.
// Example:
// Input: ‘s1’  = “abcab”, ‘s2’ = “cbab”
// Output: “bab”


#include <bits/stdc++.h>
using namespace std;

// bottom up sol
string solve(string &s, string &t, int m, int n){
    
    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s[i] ==t[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else{
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }

    string ans="";
    int i=0, j=0;
    while(dp[i][j] > 0){
        if(s[i] == t[j]){
            ans += s[i];
            i++; j++;
        }
        else{
            if(dp[i+1][j] > dp[i][j+1]){
                i++;
            }
            else{
                j++;
            }
        }
    }
    return ans;   
    
}


string findLCS(int n, int m,string &s1, string &s2){
    return solve( s1, s2, n, m);
}


int main(){
    string s1  = "abcab"; 
    string s2 = "cbab"; 
    int n=s1.size(), m=s2.size();

    cout<<findLCS(n, m, s1, s2)<<endl;
    return 0;
}