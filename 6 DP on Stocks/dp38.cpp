//  Best Time to Buy and Sell Stock IV
// Problem statement
// You have been given an array 'PRICES' consisting of 'N' integers where PRICES[i] denotes the price of a given stock on the i-th day. You are also given an integer 'K' denoting the number of possible transactions you can make.
// Your task is to find the maximum profit in at most K transactions. A valid transaction involves buying a stock and then selling it.
// Note
// You can’t engage in multiple transactions simultaneously, i.e. you must sell the stock before rebuying it.
// For Example
// Input: N = 6 , PRICES = [3, 2, 6, 5, 0, 3] and K = 2.
// Output: 7
// Explanation : The optimal way to get maximum profit is to buy the stock on day 2(price = 2) and sell it on day 3(price = 6) and rebuy it on day 5(price = 0) and sell it on day 6(price = 3). The maximum profit will be (6 - 2) + (3 - 0) = 7.


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
int dp[5001][2][2501];
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
int solve3(vector<int> &prices, int n, int k){
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(k+2, 0)));

    for(int idx=n-1; idx>=0; idx--){
        for(int buy = 0; buy<=1; buy++){
            for(int count=1; count<k+1; count++){
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
    return dp[0][1][k];
}

// bottom up sol->space optimisation
int solve4(vector<int> &prices, int n, int k){
    vector<vector<int>> prev(2, vector<int>(k+1, 0)), curr(2, vector<int>(k+2, 0));

    for(int idx=n-1; idx>=0; idx--){
        for(int buy = 0; buy<=1; buy++){
            for(int count=1; count<k+1; count++){
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
    return prev[1][k];
}


int maximumProfit(vector<int> &prices, int n, int k)
{
    
    // // recursive solution
    // return solve1(prices,n, 0, 1, k);

    // // memoization solution
    // memset(dp, -1, sizeof(dp));
    // return solve2(prices,n, 0, 1, k);

    // // bottomup solution
    // return solve3(prices, n, k);

    // bottomup solution ->space optimisation
    return solve4(prices, n, k);
}


int main(){
    vector<int> prices ={3, 2, 6, 5, 0, 3};
    int n=prices.size(); int k=2;
    cout<<maximumProfit(prices, n, k)<<endl;
    return 0;
}