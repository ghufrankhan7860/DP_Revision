// Coin Change
// You are given an array of ‘N’ distinct integers and an integer ‘X’ representing the target sum. You have to tell the minimum number of elements you have to take to reach the target sum ‘X’.
// Note:
// You have an infinite number of elements of each type.
// For example
// If N=3 and X=7 and array elements are [1,2,3]. 
// Way 1 - You can take 4 elements  [2, 2, 2, 1] as 2 + 2 + 2 + 1 = 7.
// Way 2 - You can take 3 elements  [3, 3, 1] as 3 + 3 + 1 = 7.
// Here, you can see in Way 2 we have used 3 coins to reach the target sum of 7.
// Hence the output is 3.

#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(vector<int> &num, int idx, int x){
    if(x==0)    return 0;

    if(idx < 0)     return 1e9;

    int take = 1e9;

    if(x>=num[idx])
        take = 1 + solve1(num, idx, x-num[idx]);
    int skip = solve1(num, idx-1, x);

    return min(take, skip);
}

// memoization sol
int dp[16][10001];
int solve2(vector<int> &num, int idx, int x){
    if(x==0)    return 0;

    if(idx < 0)     return 1e9;
    
    if(dp[idx][x] != -1)    return dp[idx][x];

    int take = 1e9;

    if(x>=num[idx])
        take = 1 + solve2(num, idx, x-num[idx]);
    int skip = solve2(num, idx-1, x);

    return dp[idx][x] = min(take, skip);
}

// bottom up sol
int solve3(vector<int> &num, int x){
    int n = num.size();
    vector<vector<int>> dp(n+1, vector<int>(x+1, 1e9));

    // base case
    for(int i=0; i<=n; i++) dp[i][0] = 0;
    
    for(int idx = 0; idx<n; idx++){
        for(int k = 1; k<=x; k++){
            int take = 1e9, skip = 1e9;

            if(k>=num[idx])
                take = 1 + dp[idx][k-num[idx]];
            if(idx-1>=0)
                skip = dp[idx-1][k];

            dp[idx][k] = min(take, skip);
        }
    }

    return dp[n-1][x];

}


int minimumElements(vector<int> &num, int x)
{
    sort(num.begin(), num.end());
    int n = num.size();

    // // recursive sol
    // return solve1(num, n-1, x);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(num, n-1, x);
    
    // bottom up sol
    return solve3(num, x);
}

int main(){
    
    vector<int> num = {1,2,3};
    int tar = 7;
    cout<<minimumElements(num, tar)<<endl;
    return 0;
}