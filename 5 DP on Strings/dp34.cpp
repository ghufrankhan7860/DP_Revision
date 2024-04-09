//  Wildcard Pattern Matching
// Problem statement
// Given a text and a wildcard pattern of size N and M respectively, implement a wildcard pattern matching algorithm that finds if the wildcard pattern is matched with the text. The matching should cover the entire text not partial text.
// The wildcard pattern can include the characters ‘?’ and ‘*’
//  ‘?’ – matches any single character 
//  ‘*’ – Matches any sequence of characters(sequence can be of length 0 or more)
// Sample Input 1:
// 3
// ?ay
// ray
// ab*cd
// abdefcd
// ab?d
// abcc
// Sample Output 1:
// True
// True
// False

#include <bits/stdc++.h>
using namespace std;

// recursive solution
int solve1(string &pattern, string &text, int i, int j){
    if(i==pattern.size() && j==text.size())  return true;

    if(i>=pattern.size())   return false;

    if(j>=text.size()){
        for(i; i<pattern.size(); i++){
            if(pattern[i] != '*')   return false;
        }
        return true;
    }

    if(pattern[i] == text[j] || pattern[i] == '?'){
        return solve1(pattern, text, i+1, j+1);
    }
    else if(pattern[i] == '*'){
        return (solve1(pattern, text, i+1, j) || solve1(pattern, text, i, j+1));
    }
    return false;
}


// memoization solution
int dp[201][201];
int solve2(string &pattern, string &text, int i, int j){
    if(i==pattern.size() && j==text.size())  return true;

    if(i>=pattern.size())   return false;

    if(j>=text.size()){
        for(i; i<pattern.size(); i++){
            if(pattern[i] != '*')   return false;
        }
        return true;
    }
    if(dp[i][j] != -1)  return dp[i][j];

    if(pattern[i] == text[j] || pattern[i] == '?'){
        return dp[i][j]= solve2(pattern, text, i+1, j+1);
    }
    else if(pattern[i] == '*'){
        return  dp[i][j]= (solve2(pattern, text, i+1, j) || solve2(pattern, text, i, j+1));
    }
    return  dp[i][j] = false;
}

// bottom up solution
int solve3(string &pattern, string &text){
    int m=pattern.size();
    int n=text.size();

    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    // base case initialisation
    for(int i=m-1; i>=0; i--){
        if(pattern[i] == '*') dp[i][n] = 1;
        else break;
    }

    dp[m][n] = 1;

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(pattern[i] == text[j] || pattern[i] == '?'){
                dp[i][j]= dp[i+1][j+1];
            }
            else if(pattern[i] == '*'){
                dp[i][j]= dp[i+1][j] || dp[i][j+1];
            }
        }
    }
    return dp[0][0];
}


// bottom up solution->space optimisation
int solve4(string &s1, string &s2){
    int m=s1.size(), n=s2.size();

    vector<int> prev(n+1, 0), curr(n+1, 0);

    prev[n]=1;

    if(s1[m-1]=='*')    curr[n] =1;

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(s1[i]==s2[j] || s1[i]=='?') curr[j] = prev[j+1];
            else{
                if(s1[i]=='*'){
                    curr[j] = curr[j+1] || prev[j];
                }
                else curr[j] = 0;
            }
        }
        prev=curr;
    }

    return prev[0];

}

bool wildcardMatching(string pattern, string text)
{
    // // recursive sol
    // return solve1(pattern, text, 0, 0);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(pattern, text, 0, 0);

    //  // bottomup sol
    //  return solve3(pattern, text);

    // bottomup sol->space optimisation
    return solve4(pattern, text);
}


int main(){
    string a = "*zmat***";
    string b = "azmatazmatazmat";
    cout<<wildcardMatching(a, b)<<endl;
    return 0;
}