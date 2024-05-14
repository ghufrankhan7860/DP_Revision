// Minimum insertions to make a string palindrome
// Problem statement
// A palindrome string is one that reads the same backward as well as forward.
// You are given a string 'str'.
// Find the minimum number of characters needed to insert in 'str' to make it a palindromic string
// Example :
// Input: 'str' = "abca"
// Output: 1
// Explanation:
// If we insert the character ‘b’ after ‘c’, we get the string "abcba", which is a palindromic string. Please note that there are also other ways possible.

#include <bits/stdc++.h>
using namespace  std;

// recursive sol
int solve1(string &s1, string &s2, int i, int j){
    if(i>=s1.size() || j>=s2.size())    return 0;

    if(s1[i] == s2[j])  return 1 + solve1(s1, s2, i+1, j+1);

    else return max(solve1(s1,s2, i+1, j), solve1(s1, s2, i, j+1));

}
// memoization sol
int dp[1001][1001];
int solve2(string &s1, string &s2, int i, int j){
    if(i>=s1.size() || j>=s2.size())    return 0;

    if(dp[i][j] != -1)  return dp[i][j];
    if(s1[i] == s2[j])  return  dp[i][j]= 1 + solve2(s1, s2, i+1, j+1);

    else return dp[i][j]= max(solve2(s1,s2, i+1, j), solve2(s1, s2, i, j+1));

}

int solve3(string &s, string &t){
    int m=s.size();
    vector<vector<int>> dp(m+1, vector<int> (m+1, 0));

    for(int i=m-1; i>=0; i--){
        for(int j=m-1; j>=0; j--){
            if(s[i] ==t[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else{
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }

    return m-dp[0][0];
}

// space optimisation
int solve4(string &s, string &t){
    int m=s.size();
    vector<int> prev(m+1, 0), curr(m+1, 0);

    for(int i=m-1; i>=0; i--){
        for(int j=m-1; j>=0; j--){
            if(s[i] ==t[j]) curr[j] = 1 + prev[j+1];
            else{
                curr[j] = max(prev[j], curr[j+1]);
            }
        }
        prev=curr;
    }

    return m-prev[0];
}
int minimumInsertions(string &s)
{
    string t=s;
    reverse(t.begin(), t.end());

//    // recursive sol
//    int lcs1 = solve1(s, t, 0, 0);
//    return s.size()-lcs1;

//    // memoization sol
//    memset(dp, -1, sizeof(dp));
//    int lcs2 = solve2(s, t, 0, 0);
//    return s.size()-lcs2;

//    // bottomupDp sol
//    return solve3(s, t);

    // bottomup space optimisation sol
    return solve4(s, t);
}

int main(){
    string s = "abca";
    cout<<minimumInsertions(s)<<endl;
    return 0;
}