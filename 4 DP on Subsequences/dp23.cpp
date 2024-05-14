//  Problem -> Unbounded Knapsack
// Problem statement
// You are given ‘n’ items with certain ‘profit’ and ‘weight’ and a knapsack with weight capacity ‘w’.
// You need to fill the knapsack with the items in such a way that you get the maximum profit. You are allowed to take one item multiple times.
// Example:
// Input: 
// 'n' = 3, 'w' = 10, 
// 'profit' = [5, 11, 13]
// 'weight' = [2, 4, 6]
// Output: 27

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(int n, int w, int idx, vector<int> &profit, vector<int> &weight){
    if(idx>=n)  return 0;

    int take=0;
    if(weight[idx]<=w){
        take = profit[idx] + solve1(n, w-weight[idx], idx, profit, weight);
    }
    int skip = solve1(n, w, idx+1, profit, weight);
    return max(take , skip);
}

// memoization sol
int dp[1001][1001];
int solve2(int n, int w, int idx, vector<int> &profit, vector<int> &weight){
    if(idx>=n)  return 0;

    if(dp[idx][w] != -1)    return dp[idx][w];

    int take=0;
    if(weight[idx]<=w){
        take = profit[idx] + solve2(n, w-weight[idx], idx, profit, weight);
    }
    int skip = solve2(n, w, idx+1, profit, weight);
    return dp[idx][w] = max(take , skip);
}

// bottomup sol
int solve3(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<vector<int>> dp(n+1, vector<int>(w+1, 0));

    for(int idx=n-1; idx>=0; idx--){
        for(int wt=1; wt<=w; wt++){
            int take=0;
            int skip = dp[idx+1][wt];
            dp[idx][wt] = max(take, skip);
        }
    }
    return dp[0][w];
}
// bottomup sol->space optimised
int solve4(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<int> prev(w+1, 0), curr(w+1, 0);

    for(int idx=n-1; idx>=0; idx--){
        for(int wt=1; wt<=w; wt++){
            int take=0;
            if(wt-weight[idx]>=0){
                take = profit[idx] + curr[wt-weight[idx]];
            }
            int skip = prev[wt];
            curr[wt] = max(take, skip);
        }
        prev=curr;
    }
    return prev[w];
}

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight) {
    // // recursive sol
    // return solve1(n,w, 0, profit, weight);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(n,w, 0, profit, weight);

    // // bottomup sol
    // return solve3(n,w, profit, weight);

    // bottomup sol ->space optimisation
    return solve4(n,w, profit, weight);

}
int main(){
    int n = 3;
    int w = 10;
    vector<int> profit = {5,11,13};
    vector<int> weight = {2, 4, 6};

    cout<<unboundedKnapsack(n, w, profit, weight)<<endl;
    return 0;
}