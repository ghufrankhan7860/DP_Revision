// Distinct Subsequences
// Problem statement
// A Subsequence of a string is the string that is obtained by deleting 0 or more letters from the string and keeping the rest of the letters in the same order.
// We are given two strings, 'str' and 'sub'.
// Find the number of subsequences of 'str' which are equal to 'sub'.
// Since the answer can be very large, print it modulo 10 ^ 9 + 7.
// Example :
// Input: 'str' = “brootgroot” and 'sub' = “brt”
// Output: 3

#include <bits/stdc++.h>
using namespace std;

int mod= 1e9+7;

// recursive sol
int solve1(string &a, string &b, int i, int j){
    if(j>=b.size()) return 1;
    if(i>=a.size()) return 0;

    long take=0, skip=0;
    if(a[i] == b[j]){
        take = solve1(a, b, i+1, j+1);
    }
    skip = solve1(a, b, i+1, j);

    return (take + skip)%mod;
}

// memoization sol
int dp[1001][1001];
int solve2(string &a, string &b, int i, int j){
    if(j>=b.size()) return 1;
    if(i>=a.size()) return 0;
    
    if(dp[i][j] != -1)  return dp[i][j];

    long take=0, skip=0;
    if(a[i] == b[j]){
        take = solve2(a, b, i+1, j+1);
    }
    skip = solve2(a, b, i+1, j);

    return dp[i][j] = (take + skip)%mod;
}

// bottom up solution
int solve3(string &a, string &b){
    int m=a.size(), n=b.size();
    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

    for(int i=0; i<=m; i++)  dp[i][n] = 1;

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            long take=0, skip=0;
            if(a[i] == b[j]){
                take = dp[i+1][j+1];
            }
            skip = dp[i+1][j];

            dp[i][j] = (take + skip)%mod;
        }
    }

    return dp[0][0];
}

// bottom up solution->space optimisation
int solve4(string &a, string &b){
    int m=a.size(), n=b.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);

    prev[n] = 1;

    for(int i=m-1; i>=0; i--){
        curr[n] = 1;
        for(int j=n-1; j>=0; j--){
            long take=0, skip=0;
            if(a[i] == b[j]){
                take = prev[j+1];
            }
            skip = prev[j];

            curr[j] = (take + skip)%mod;
        }
        prev=curr;
    }

    return prev[0];
}

int distinctSubsequences(string &str, string &sub)
{
    // // recursive sol
	// return solve1(str, sub, 0, 0);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
	// return solve2(str, sub, 0, 0);

    // // bottom up sol
	// return solve3(str, sub);

    // bottom up sol
	return solve4(str, sub);
}

int main(){
    string s="brootgroot";
    string t="brt";
    cout<<distinctSubsequences(s, t)<<endl;
    return 0;
}