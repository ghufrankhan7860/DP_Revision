//  Best Time to Buy and Sell Stock with Transaction Fee
// Problem statement
// You are given an array 'prices' of size 'n', denoting the price of stocks on 'n' days.
// Rahul can buy one stock at a time, and he must sell it before buying stock on another day.
// The entire transaction of selling and buying the stock requires some transaction fee, given as 'fee'.
// Find the maximum profit Rahul can achieve by trading on the stocks.
// Example :
// Input: 'prices' =  [1, 2, 3] and 'fee' = 1
// Output: 1

#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

// recursive solution
long solve1(vector<int> &values, int n, int idx, int buy, int fee){
    
    if(idx>=n)  return 0;

    long profit = 0;
    if(buy){
        profit = max(-values[idx] + solve1(values, n, idx+1, 0, fee), solve1(values, n, idx+1, 1, fee));
    }
    else{
        profit = max(values[idx] + solve1(values, n, idx+1, 1, fee) -fee , solve1(values, n, idx+1, 0, fee));
    }
    return profit;
}


// memoization solution
long dp[100001][2];
long solve2(vector<int> &values, int n, int idx, int buy, int fee){
    
    if(idx>=n)  return 0;

    if(dp[idx][buy] != -1)  return dp[idx][buy];
    long profit = 0;
    if(buy){
        profit = max(-values[idx] + solve2(values, n, idx+1, 0, fee), solve2(values, n, idx+1, 1, fee));
    }
    else{
        profit = max(values[idx] + solve2(values, n, idx+1, 1, fee) -fee, solve2(values, n, idx+1, 0, fee));
    }
    return  dp[idx][buy] = profit;
}

// bottom up solution
long solve3(vector<int> &values, int n, int fee){
    vector<vector<long>> dp(n+1, vector<long>(2, 0));

    for(int idx=n-1; idx>=0;  idx--){
        for(int buy=0; buy<=1; buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[idx] + dp[idx+1][0], dp[idx+1][1]);
            }
            else{
                profit = max(values[idx] + dp[idx+1][1] -fee, dp[idx+1][0]);
            }
            dp[idx][buy] = profit;
        }
    }
    return dp[0][1];
}


// bottom up solution->space optimisation
long solve4(vector<int> &values, int n, int fee){
    vector<long> prev(2, 0), curr(2, 0);

    for(int idx=n-1; idx>=0;  idx--){
        for(int buy=0; buy<=1; buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[idx] + prev[0], prev[1]);
            }
            else{
                profit = max(values[idx] + prev[1] -fee, prev[0]);
            }
            curr[buy] = profit;
        }
        prev=curr;
    }
    return prev[1];
}


int maximumProfit(vector<int> &prices, int n, int fee)
{
    // // recursive sol
    // return solve1(prices, n, 0, 1, fee);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(prices, n, 0, 1, fee);
    
    // // bottomup sol
    // return solve3(prices , n, fee);
    
    // bottomup sol->space optimisation
    return solve4(prices , n, fee);
}

int main(){
    
    return 0;
}