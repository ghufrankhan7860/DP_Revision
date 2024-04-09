//  Best Time to Buy and Sell Stock with Cooldown
// Problem statement
// You are given a list of stock prices of size 'n' called ‘prices’, where ‘prices[i]’ represents the price on ‘i’th day.
// Your task is to calculate the maximum profit you can earn by trading stocks if you can only hold one stock at a time.
// After you sell your stock on the ‘i’th day, you can only buy another stock on ‘i + 2’ th day or later.
// Example:
// Input: 'prices' = [4, 9, 0, 4, 10]
// Output: 11


#include <bits/stdc++.h>
using namespace std;

// recursive sol
long solve1(vector<int> &prices, int buy, int idx, int n){

    if(idx >=n) return 0;

    long profit = 0;
    if(buy){
        profit = max(-prices[idx] + solve1(prices, 0, idx+1, n), solve1(prices, 1, idx+1, n));
    }
    else{
        profit = max(prices[idx] + solve1(prices, 1, idx+2, n), solve1(prices, 0, idx+1, n));
    }
    return profit;
}


// memoization sol
long dp[2][100001];
long solve2(vector<int> &prices, int buy, int idx, int n){

    if(idx >=n) return 0;

    if(dp[buy][idx] != -1)    return dp[buy][idx];

    long profit = 0;
    if(buy){
        profit = max(-prices[idx] + solve1(prices, 0, idx+1, n), solve1(prices, 1, idx+1, n));
    }
    else{
        profit = max(prices[idx] + solve1(prices, 1, idx+2, n), solve1(prices, 0, idx+1, n));
    }
    return dp[buy][idx] = profit;
}

// bottom up solution
int solve3(vector<int> &prices, int n){

    vector<vector<long>> dp(2, vector<long>(n+2,0));

    for(int idx=n-1; idx>=0; idx--){
        for(int buy=0; buy<=1; buy++){
            if(buy){
                dp[buy][idx] = max(-prices[idx] + dp[0][idx+1], dp[1][idx+1]);
            }
            else{
                dp[buy][idx] = max(prices[idx] + dp[1][idx+2], dp[0][idx+1]);
            }
        }
    }
    return dp[1][0];
}

// bottom up solution->space optimisation
int solve4(vector<int> &prices, int n){

    vector<long> prevprev(2,0), prev(2,0), curr(2,0);

    for(int idx=n-1; idx>=0; idx--){
        for(int buy=0; buy<=1; buy++){
            if(buy){
                curr[1] = max(-prices[idx] + prev[0], prev[1]);
            }
            else{
                curr[0] = max(prices[idx] + prevprev[1], prev[0]);
            }
        }
        prevprev=prev;
        prev=curr;
    }
    return prev[1];
}

int stockProfit(vector<int> &prices){
    int n=prices.size();
    // // recursive sol
    // return solve1(prices, 1, 0, n);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(prices, 1, 0, n);

    // // bottomup sol
    // return solve3(prices , n);

    // bottomup sol->space optimisation
    return solve4(prices , n);
}

int main(){
    
    return 0;
}