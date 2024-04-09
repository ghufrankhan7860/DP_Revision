// Longest Palindromic Subsequence
// Problem statement
// You have been given a string ‘A’ consisting of lower case English letters. Your task is to find the length of the longest palindromic subsequence in ‘A’.
// A subsequence is a sequence generated from a string after deleting some or no characters of the string without changing the order of the remaining string characters. (i.e. “ace” is a subsequence of “abcde” while “aec” is not).
// A string is said to be palindrome if the reverse of the string is the same as the actual string. For example, “abba” is a palindrome, but “abbc” is not a palindrome.
// Sample Input 1:
// 2
// bbabcbcab
// bbbab
// Sample Output 1:
// 7
// 4

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(string &s, string &t, int i, int j){
    if(i>=s.size() || j>=t.size())  return 0;

    if(s[i] == t[j]){
        return 1 + solve1(s, t, i+1, j+1);
    }
    else    return max(solve1(s, t, i, j+1), solve1(s, t, i+1, j));
}

// memoization sol
int dp[101][101];
int solve2(string &s, string &t, int i, int j){
    if(i>=s.size() || j>=t.size())  return 0;

    if(dp[i][j] != -1)  return dp[i][j];

    if(s[i] == t[j]){
        return  dp[i][j] = 1 + solve2(s, t, i+1, j+1);
    }
    else    return  dp[i][j] = max(solve2(s, t, i, j+1), solve2(s, t, i+1, j));
}

// bottom up solution
int solve3(string &s, string &t){
    int m=s.size(), n=t.size();

    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s[i] == t[j]){
                dp[i][j] = 1 + dp[i+1][j+1];
            }
            else{
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }
    return dp[0][0];
}

// bottom up solution->space optimisation
int solve4(string &s, string &t){
    int m=s.size(), n=t.size();

    vector<int> prev(n+1, 0), curr(n+1, 0);

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s[i] == t[j]){
                curr[j] = 1 + prev[j+1];
            }
            else{
                curr[j] = max(prev[j], curr[j+1]);
            }
        }
        prev=curr;
    }
    return prev[0];
}

int longestPalindromeSubsequence(string s)
{
    string t=s;
    reverse(t.begin(), t.end());

    // // recursive sol
    // return solve1(s, t, 0, 0);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(s, t, 0, 0);
    
    // // bottomupDp sol
    // return solve3(s, t);

    // bottomupDp sol->space optimisation
    return solve4(s, t);
}

int main(){
    string s = "bbabcbcab";
    cout<<longestPalindromeSubsequence(s)<<endl;
    return 0;
}