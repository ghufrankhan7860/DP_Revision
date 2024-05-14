// Rod cutting problem
// Problem statement
// Given a rod of length ‘N’ units. The rod can be cut into different sizes and each size has a cost associated with it. Determine the maximum cost obtained by cutting the rod and selling its pieces.
// Note:
// 1. The sizes will range from 1 to ‘N’ and will be integers.
// 2. The sum of the pieces cut should be equal to ‘N’.
// 3. Consider 1-based indexing.

// Sample Input 1:
// 2
// 5
// 2 5 7 8 10
// 8
// 3 5 8 9 10 17 17 20
// Sample Output 1:
// 12
// 24


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
            if(wt-weight[idx]>=0){
                take = profit[idx] + dp[idx][wt-weight[idx]];
            }
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

int cutRod(vector<int> &price, int n)
{
    int w = n;
    vector<int> weight(n,0);
    for(int i=1; i<=n; i++)	weight[i-1]=i;
    // // recursive sol
    // return solve1(n,w, 0, profit, weight);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(n,w, 0, profit, weight);

    // // bottomup sol
    // return solve3(n,w, profit, weight);

    // bottomup sol ->space optimisation

    return solve4(n,w, price, weight);
}

int main(){
    int n = 5;
    vector<int> prices = {2, 5, 7, 8, 10};
    cout<<cutRod(prices, n)<<endl;
    return 0;
}