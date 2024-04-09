//  0 1 Knapsack
// Problem statement
// A thief is robbing a store and can carry a maximal weight of W into his knapsack. There are N items and the ith item weighs wi and is of value vi. Considering the constraints of the maximum weight that a knapsack can carry, you have to find and return the maximum value that a thief can generate by stealing items.
// Sample Input:
// 1 
// 4
// 1 2 4 5
// 5 4 8 6
// 5
// Sample Output:
// 13

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(vector<int> &w, vector<int> &val, int n, int maxWeight, int idx){
    if(idx >= n)  return 0;
    
    int take = 0, skip = 0;
    if(maxWeight >= w[idx]){
        take = val[idx] + solve1(w, val, n, maxWeight-w[idx], idx+1);
    }
    skip = solve1(w, val, n, maxWeight, idx+1);

    return max(take, skip);
}

// memoization sol
int dp[101][1001];
int solve2(vector<int> &w, vector<int> &val, int n, int maxWeight, int idx){
    if(idx>=n)  return 0;
    
    if(dp[idx][maxWeight] != -1)    return dp[idx][maxWeight];

    int take = 0, skip = 0;
    if(maxWeight >= w[idx]){
        take = val[idx] + solve2(w, val, n, maxWeight-w[idx], idx+1);
    }
    skip = solve2(w, val, n, maxWeight, idx+1);

    return dp[idx][maxWeight] = max(take, skip);
}

// bottom up sol
int solve3(vector<int> &w, vector<int> &val, int n, int maxWeight){
   
    vector<vector<int>> dp(n+1, vector<int> (maxWeight+1, 0));

    for(int idx=n-1; idx>=0; idx--){
        for(int k=1; k<=maxWeight; k++){
            int take = 0, skip = 0;
            if(k >= w[idx]){
                take = val[idx] + dp[idx+1][k-w[idx]];
            }
            skip = dp[idx+1][k];

            dp[idx][k] = max(take, skip);
        }
    }
    return dp[0][maxWeight];
}

// bottom up sol->space optimisation
int solve4(vector<int> &w, vector<int> &val, int n, int maxWeight){
   
    vector<int> prev(maxWeight+1, 0), curr(maxWeight+1, 0);

    for(int idx=n-1; idx>=0; idx--){
        for(int k=1; k<=maxWeight; k++){
            int take = 0, skip = 0;
            if(k >= w[idx]){
                take = val[idx] + prev[k-w[idx]];
            }
            skip = prev[k];

            curr[k] = max(take, skip);
        }
        prev=curr;
    }
    return prev[maxWeight];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
{
    // // recursive sol
    // return solve1(weight, value, n, maxWeight, 0);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(weight, value, n, maxWeight, 0);

    // // bottom up
    // return solve3(weight, value, n, maxWeight);

    // bottom up->space optimisation
    return solve4(weight, value, n, maxWeight);
}


int main(){
    vector<int> weight = {1,2,4,5};
    vector<int> val = {5,4,8,6};
    int maxWeight = 5;
    int n=weight.size();
    cout<<knapsack(weight, val, n, maxWeight)<<endl;
    return 0;
}