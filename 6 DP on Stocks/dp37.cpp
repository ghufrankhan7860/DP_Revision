//  Best Time to Buy and Sell Stock III
// Problem statement
// You are Harshad Mehta’s friend. He told you the price of a particular stock for the next ‘n’ days.
// You are given an array ‘prices’ which such that ‘prices[i]’ denotes the price of the stock on the ith day.
// You don't want to do more than 2 transactions. Find the maximum profit that you can earn from these transactions.
// Note
// 1. Buying a stock and then selling it is called one transaction.
// 2. You are not allowed to do multiple transactions at the same time. This means you have to sell the stock before buying it again. 
// Example:
// Input: ‘n’ = 7, ‘prices’ = [3, 3, 5, 0, 3, 1, 4].
// Output: 6'

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(vector<int> &prices, int n, int idx, int buy, int count){
    
    if(count ==0 || idx>=n)  return 0;

    int profit = 0;
    if(buy){
        profit = max(-prices[idx] + solve1(prices, n, idx+1, 0, count), solve1(prices, n, idx+1, 1, count));
    }
    else{
        profit = max(prices[idx] + solve1(prices, n, idx+1, 1, count-1), solve1(prices, n, idx+1, 0, count));
    }
    return profit;
}

// memoization sol
int dp[1000001][2][3];
int solve2(vector<int> &prices, int n, int idx, int buy, int count){
    
    if(count ==0 || idx>=n)  return 0;

    if(dp[idx][buy][count] != -1)   return dp[idx][buy][count];
    int profit = 0;
    if(buy){
        profit = max(-prices[idx] + solve2(prices, n, idx+1, 0, count), solve2(prices, n, idx+1, 1, count));
    }
    else{
        profit = max(prices[idx] + solve2(prices, n, idx+1, 1, count-1), solve2(prices, n, idx+1, 0, count));
    }
    return  dp[idx][buy][count]=profit;
}

// bottom up sol
int solve3(vector<int> &prices, int n){
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));

    for(int idx=n-1; idx>=0; idx--){
        for(int buy = 0; buy<=1; buy++){
            for(int count=1; count<3; count++){
                int profit = 0;
                if(buy){
                    profit = max(-prices[idx] + dp[idx+1][0][count], dp[idx+1][1][count]);
                }
                else{
                    profit = max(prices[idx] + dp[idx+1][1][count-1], dp[idx+1][0][count]);
                }
                dp[idx][buy][count]=profit; 
            }
        }
    }
    return dp[0][1][2];
}

// bottom up sol->space optimisation
int solve4(vector<int> &prices, int n){
    vector<vector<int>> prev(2, vector<int>(3, 0)), curr(2, vector<int>(3, 0));

    for(int idx=n-1; idx>=0; idx--){
        for(int buy = 0; buy<=1; buy++){
            for(int count=1; count<3; count++){
                int profit = 0;
                if(buy){
                    profit = max(-prices[idx] + prev[0][count], prev[1][count]);
                }
                else{
                    profit = max(prices[idx] + prev[1][count-1], prev[0][count]);
                }
                curr[buy][count]=profit; 
            }
            prev=curr;
        }
    }
    return prev[1][2];
}

int maxProfit(vector<int>& prices)
{
    int n=prices.size();
    // recursive solution
    return solve1(prices, n, 0, 1, 2);

    // // memoization solution
    // memset(dp, -1, sizeof(dp));
    // return solve2(prices, n, 0, 1, 2);

    // // bottomup solution
    // return solve3(prices, n);

    // // bottomup solution ->space optimisation
    // return solve4(prices, n);
}


int main(){
    vector<int> prices= {3, 3, 5, 0, 3, 1, 4};
    cout<<maxProfit(prices)<<endl;
    return 0;
}