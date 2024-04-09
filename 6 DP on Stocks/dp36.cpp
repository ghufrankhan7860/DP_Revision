//  Best Time to Buy and Sell Stock II
// Problem statement
// You have been given stock values/prices for N number of days. Every i-th day signifies the price of a stock on that day. Your task is to find the maximum profit which you can make by buying and selling the stocks.
//  Note :
// You may make as many transactions as you want but can not have more than one transaction at a time i.e, if you have the stock, you need to sell it first, and then only you can buy it again.
// Sample Input 1 :
// 1
// 7
// 1 2 3 4 5 6 7
// Sample Output 1 :
// 6

#include <bits/stdc++.h>
using namespace std;

// recursive solution
long solve1(long *values, int n, int idx, int buy){
    
    if(idx>=n)  return 0;

    long profit = 0;
    if(buy){
        profit = max(-values[idx] + solve1(values, n, idx+1, 0), solve1(values, n, idx+1, 1));
    }
    else{
        profit = max(values[idx] + solve1(values, n, idx+1, 1), solve1(values, n, idx+1, 0));
    }
    return profit;
}


// memoization solution
long dp[100001][2];
long solve2(long *values, int n, int idx, int buy){
    
    if(idx>=n)  return 0;

    if(dp[idx][buy] != -1)  return dp[idx][buy];
    long profit = 0;
    if(buy){
        profit = max(-values[idx] + solve2(values, n, idx+1, 0), solve2(values, n, idx+1, 1));
    }
    else{
        profit = max(values[idx] + solve2(values, n, idx+1, 1), solve2(values, n, idx+1, 0));
    }
    return  dp[idx][buy] = profit;
}

// bottom up solution
long solve3(long *values, int n){
    vector<vector<long>> dp(n+1, vector<long>(2, 0));

    for(int idx=n-1; idx>=0;  idx--){
        for(int buy=0; buy<=1; buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[idx] + dp[idx+1][0], dp[idx+1][1]);
            }
            else{
                profit = max(values[idx] + dp[idx+1][1], dp[idx+1][0]);
            }
            dp[idx][buy] = profit;
        }
    }
    return dp[0][1];
}


// bottom up solution->space optimisation
long solve4(long *values, int n){
    vector<long> prev(2, 0), curr(2, 0);

    for(int idx=n-1; idx>=0;  idx--){
        for(int buy=0; buy<=1; buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[idx] + prev[0], prev[1]);
            }
            else{
                profit = max(values[idx] + prev[1], prev[0]);
            }
            curr[buy] = profit;
        }
        prev=curr;
    }
    return prev[1];
}


long getMaximumProfit(long *values, int n)
{
    // // recursive sol
    // return solve1(values, n, 0, 1);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(values, n, 0, 1);

    // // bottomup sol
    // return solve3(values , n);

    // bottomup sol->space optimisation
    return solve4(values , n);
}


int main(){
    vector<long> prices={1,2,3,4,5,6,7};
    int n=prices.size();
    long * values = new long[n];
    for(int i=0; i<n; i++)  values[i] = prices[i];
    cout<<getMaximumProfit(values, n)<<endl;
    return 0;
}