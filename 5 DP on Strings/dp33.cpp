//  Edit Distance
// Problem statement
// You are given two strings 'S' and 'T' of lengths 'N' and 'M' respectively. Find the "Edit Distance" between the strings.
// Edit Distance of two strings is the minimum number of steps required to make one string equal to the other. In order to do so, you can perform the following three operations:
// 1. Delete a character
// 2. Replace a character with another one
// 3. Insert a character
// Note:
// Strings don't contain spaces in between.
// Sample Input 1 :
// abc
// dc
// Sample Output 1 :
// 2

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(string &a, string &b, int i, int j){
    if(i==a.size() && j==b.size())  return 0;

    if(i>=a.size()) return b.size()-j;
    if(j>=b.size()) return a.size()-i;

    int ins=1e9, del = 1e9, rep=1e9;

    if(a[i] == b[j]) return solve1(a, b, i+1, j+1);
    
    ins = solve1(a, b, i, j+1);
    del = solve1(a, b, i+1, j);
    rep = solve1(a, b, i+1, j+1);

    return 1+min(ins, min(del, rep));
}

// memoization sol
int dp[1001][1001];
int solve2(string &a, string &b, int i, int j){
    if(i==a.size() && j==b.size())  return 0;

    if(i>=a.size()) return b.size()-j;
    if(j>=b.size()) return a.size()-i;

    if(dp[i][j] != -1)  return dp[i][j];

    if(a[i] == b[j]) return dp[i][j] = solve2(a, b, i+1, j+1);

    int ins=1e9, del = 1e9, rep=1e9;

    ins = solve2(a, b, i, j+1);
    del = solve2(a, b, i+1, j);
    rep = solve2(a, b, i+1, j+1);

    return dp[i][j] = 1+min(ins, min(del, rep));
}

// bottom up sol
int solve3(string &a, string &b){
    int m=a.size(), n=b.size();

    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    for(int i=0; i<m; i++)  dp[i][n] = m-i;
    for(int j=0; j<n; j++)  dp[m][j] = n-j;

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(a[i] == b[j])    dp[i][j] = dp[i+1][j+1];
            else{
                int ins=1e9, del = 1e9, rep=1e9;

                ins = dp[i][j+1];
                del = dp[i+1][j];
                rep = dp[i+1][j+1];

                dp[i][j] = 1+min(ins, min(del, rep));
            }
        }
    }
    return dp[0][0];
}

// bottom up sol->space optimisation
int solve4(string &a, string &b){
    int m=a.size(), n=b.size();

    vector<int> prev(n+1, 0), curr(n+1, 0);

    // base case initialisation
    for(int j=0; j<n; j++)  prev[j] = n-j;

    for(int i=m-1; i>=0; i--){
        curr[n] = m-i;
        for(int j=n-1; j>=0; j--){
            if(a[i] == b[j])   curr[j] = prev[j+1];
            else{
                int ins=1e9, del = 1e9, rep=1e9;

                ins =curr[j+1];
                del = prev[j];
                rep = prev[j+1];

                curr[j] = 1+min(ins, min(del, rep));
            }
        }
        prev=curr;
    }
    return prev[0];
}

int editDistance(string str1, string str2)
{
    // // recursive sol
    // return solve1(str1, str2, 0, 0);

    // // memoization sol
    // memset(dp, -1 , sizeof(dp));
    // return solve2(str1, str2, 0, 0);

    // // bottomup sol
    // return solve3(str1, str2);

    // bottomup sol->space optimisation
    return solve4(str1, str2);
}



int main(){
    string a= "abc";
    string b = "dc";
    cout<<editDistance(a, b)<<endl;
    return 0;
}