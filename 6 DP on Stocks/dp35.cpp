// Best Time to Buy and Sell Stock
// Problem statement
// You are given an array/list 'prices' where the elements of the array represent the prices of the stock as they were yesterday and indices of the array represent minutes. Your task is to find and return the maximum profit you can make by buying and selling the stock. You can buy and sell the stock only once.
// Note:
// You can’t sell without buying first.
// For Example:
// For the given array [ 2, 100, 150, 120],
// The maximum profit can be achieved by buying the stock at minute 0 when its price is Rs. 2 and selling it at minute 2 when its price is Rs. 150.
// So, the output will be 148.

#include <bits/stdc++.h>
using namespace std;

int maximumProfit(vector<int> &prices){
    int n= prices.size();
    int last=prices[0];
    int profit = 0;
    for(int i=1; i<n; i++){
        profit = max(profit, prices[i]-last);
        last = min(last, prices[i]);
    }
    return profit;
}

int main(){
    vector<int> prices= {2,100,150,120};
    cout<<maximumProfit(prices)<<endl;
    return 0;
}