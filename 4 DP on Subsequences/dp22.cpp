// Problem statement
// You are given an infinite supply of coins of each of denominations D = {D0, D1, D2, D3, ...... Dn-1}. You need to figure out the total number of ways W, in which you can make a change for value V using coins of denominations from D. Print 0, if a change isn't possible.
// Sample Input 1 :
// 3
// 1 2 3
// 4
// Sample Output 1:
// 4
// Explanation for Sample Output 1:
// We can make a change for the value V = 4 in four ways.
// 1. (1,1,1,1), 
// 2. (1,1, 2), [One thing to note here is, (1, 1, 2) is same as that of (2, 1, 1) and (1, 2, 1)]
// 3. (1, 3), and 
// 4. (2, 2)

#include <bits/stdc++.h>
using namespace std;

// recursive sol
long solve1(int *denominations, int n, int value, int idx){
    if(value == 0)  return 1;
    
    if(value < 0 || idx < 0)    return 0;

    long take = 0, skip = 0;
    if(value >= denominations[idx]){
        take = solve1(denominations, n, value-denominations[idx], idx);
    } 
    skip = solve1(denominations, n, value, idx-1);

    return take + skip;

}

// memoization sol
long dp[11][2002];
long solve2(int *denominations, int n, int value, int idx){
    if(value == 0)  return 1;
    
    if(value < 0 || idx < 0)    return 0;

    if(dp[idx][value] != -1)    return dp[idx][value];

    long take = 0, skip = 0;
    if(value >= denominations[idx]){
        take = solve2(denominations, n, value-denominations[idx], idx);
    } 
    skip = solve2(denominations, n, value, idx-1);

    return dp[idx][value] = take + skip;

}

// bottom up solution
long solve3(int *denominations, int n, int value){
    vector<vector<long>> dp(n+1, vector<long>(value+1, 0));

    // base case
    for(int i= 0; i<=n; i++)    dp[i][0] = 1;

    for(int idx = 0; idx<n; idx++){
        for(int k=1; k<=value; k++){
            long take = 0, skip = 0;
            if(k >= denominations[idx]){
                take =dp[idx][k-denominations[idx]];
            } 
            skip = dp[idx-1][k];

            dp[idx][k] = take + skip;
        }
    }
    return dp[n-1][value];

}

// bottom up solution->space optimisation
long solve4(int *denominations, int n, int value){
    vector<long> prev(value+1, 0), curr(value +1, 0);

    // base case
    prev[0] = 1;

    for(int idx = 0; idx<n; idx++){
        curr[0] = 1;
        for(int k=1; k<=value; k++){
            long take = 0, skip = 0;
            if(k >= denominations[idx]){
                take =curr[k-denominations[idx]];
            } 
            skip = prev[k];

            curr[k] = take + skip;
        }
        prev = curr;
    }
    return prev[value];
}

long countWaysToMakeChange(int *denominations, int n, int value)
{
    // // recursive sol
    // return solve1(denominations, n, value, 0);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(denominations, n, value, 0);


    //  // bottom up sol
    //  return solve3(denominations, n, value);

   //' bottom up space optimised
   return solve4(denominations, n, value);

}


int main(){
    
    return 0;
}