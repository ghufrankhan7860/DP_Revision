// Longest Common Subsequence
// Problem statement
// Given two strings, 'S' and 'T' with lengths 'M' and 'N', find the length of the 'Longest Common Subsequence'.
// For a string 'str'(per se) of length K, the subsequences are the strings containing characters in the same relative order as they are present in 'str,' but not necessarily contiguous. Subsequences contain all the strings of length varying from 0 to K.
// Example :
// Subsequences of string "abc" are:  ""(empty string), a, b, c, ab, bc, ac, abc.
// Sample Input 1 :
// adebc
// dcadb
// Sample Output 1 :
// 3

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(string &s, string &t, int i, int j){
    if(i>=s.size() || j>=t.size())  return 0;

    if(s[i] == t[j]){
        return 1 + solve1(s, t, i+1, j+1);
    }
    else{
        return max(solve1(s, t, i, j+1), solve1(s, t, i+1, j));
    }
}

// memoization sol
int dp[1001][1001];
int solve2(string &s, string &t, int i, int j){
    if(i>=s.size() || j>=t.size())  return 0;

    if(dp[i][j] != -1)  return dp[i][j];
    if(s[i] == t[j]){
        return dp[i][j] = 1 + solve2(s, t, i+1, j+1);
    }
    else{
        return dp[i][j] = max(solve2(s, t, i, j+1), solve2(s, t, i+1, j));
    }
}

// bottom up sol
int solve3(string &s, string &t){
    int m=s.size(), n=t.size();
    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s[i] ==t[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else{
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }

    return dp[0][0];
    
}

// bottom up sol->space optimisation
int solve4(string &s, string &t){
    int m=s.size(), n=t.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s[i] ==t[j]) curr[j] = 1 + prev[j+1];
            else{
                curr[j] = max(prev[j], curr[j+1]);
            }
        }
        prev=curr;
    }

    return prev[0];
    
}

int lcs(string &s, string &t)
{
	// // recursive sol
	// return solve1(s, t, 0, 0);

	// // memoization sol
	// memset(dp, -1, sizeof(dp));
	// return solve2(s, t, 0, 0);

	// // bottomup sol
	// return solve3(s, t);

	// bottomup sol-> space optimised sol
	return solve4(s, t);
}

int main(){
    string s="adebc";
    string t= "dcadb";
    cout<<lcs(s, t)<<endl;
    return 0;
}