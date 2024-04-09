// Longest Common Substring
// Problem statement
// You are given two strings, 'str1' and 'str2'. You have to find the length of the longest common substring.
// A substring is a continuous segment of a string. For example, "bcd" is a substring of "abcd", while "acd" or "cda" are not.
// Example:
// Input: ‘str1’ = “abcjklp” , ‘str2’ = “acjkp”.
// Output: 3
// Explanation:  The longest common substring between ‘str1’ and ‘str2’ is “cjk”, of length 3.

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(string &s1,string & s2, int i, int j, int len){
    if(i>=s1.size() || j>=s2.size())    return len;
    
    if(s1[i] == s2[j]){
        len = max(len, solve1(s1, s2, i+1, j+1, len+1));
    }
    len = max(len, max(solve1(s1, s2, i, j+1, 0), solve1(s1, s2, i+1, j, 0)));

    return len;
}

// memoization sol
int dp[1001][1001];
int solve2(string &s1,string & s2, int i, int j, int len){
    if(i>=s1.size() || j>=s2.size())    return len;

    if(dp[i][j] != -1)  return dp[i][j];

    if(s1[i] == s2[j]){
        len = max(len, solve2(s1, s2, i+1, j+1, len+1));
    }
    
    len = max(len, max(solve2(s1, s2, i, j+1, 0), solve2(s1, s2, i+1, j, 0)));

    return dp[i][j] = len;
}


// bottom up solution
int solve3(string &s1, string &s2){
    int m = s1.size(), n=s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    int maxlen =0;
    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s1[i] == s2[j]){
                dp[i][j] = 1 +dp[i+1][j+1];
                maxlen = max(maxlen, dp[i][j]);
            }
        }
    }
    return maxlen;
}

// bottom up solution->space optimisation
int solve4(string &s1, string &s2){
    int m = s1.size(), n=s2.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);

    int maxlen =0;
    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s1[i] == s2[j]){
                curr[j] = 1 + prev[j+1];
                maxlen = max(maxlen, curr[j]);
            }
        }
        prev=curr;
    }
    return maxlen;
}

int lcs(string &str1, string &str2){

    //  // reucrsive sol
    //  return solve1(str1, str2, 0, 0, 0);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(str1, str2, 0, 0, 0);

    // // bottom up solution
    // return solve3(str1, str2);

    // // bottom up solution->space optimisation
    // return solve4(str1, str2);
}
int main(){
    string s1="abcjklp";
    string s2="acjkp";
    cout<<lcs(s1, s2)<<endl;
    return 0;
}