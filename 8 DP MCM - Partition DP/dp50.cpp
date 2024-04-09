// Problem statement
// You are given chocolate of ‘N’ length. The chocolate is labeled from 0 to ‘N’. You are also given an array ‘CUTS’ of size ‘C’, denoting the positions at which you can do a cut. The order of cuts can be changed. The cost of one cut is the length of the chocolate to be cut. Therefore, the total cost is the sum of all the cuts. Print the minimum cost to cut the chocolate.
// Note:
// All the integers in the ‘CUTS’ array are distinct.
// For example:
// Let ‘N’ be: 4
// Let the ‘CUTS’ array be: [1, 3].
// Let the order of doing the cut be [1, 3].
// The first cut of 1 on length 4 results in a cost of 4, and chocolate is split into two parts of the length of 1 and 3.
// The second cut of 3 on length 3 results in a cost of 3, and chocolate is split into two parts again of the length of 2 and 1. So the total cost is 7.
// The cost will remain the same if we change the order of cutting. So the result is 7.


#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(vector<int> &cuts, int i, int j){
    if(i>j) return 0;

    int minCost=  INT_MAX;
    for(int idx=i; idx<=j; idx++){
        minCost= min(minCost, cuts[j+1]-cuts[i-1] + solve1(cuts, i, idx-1) + solve1(cuts, idx+1, j));
    }
    return minCost;
}


// memoization sol
int dp[1002][1002];
int solve2(vector<int> &cuts, int i, int j){
    if(i>j) return 0;

    if(dp[i][j] != -1)  return dp[i][j];

    int minCost=  INT_MAX;
    for(int idx=i; idx<=j; idx++){
        minCost= min(minCost, cuts[j+1]-cuts[i-1] + solve2(cuts, i, idx-1) + solve2(cuts, idx+1, j));
    }
    return dp[i][j] = minCost;
}

//bottom up
int solve3(vector<int> &cuts){
    int c=cuts.size();

    vector<vector<int>> dp(c+1, vector<int>(c+1, 0));

    for(int i=c-2; i>=1; i--){
        for(int j=i; j<c-1; j++){
            int minCost=  INT_MAX;
            for(int idx=i; idx<=j; idx++){
                minCost= min(minCost, cuts[j+1]-cuts[i-1] + dp[i][idx-1] + dp[idx+1][j]);
            }
            dp[i][j] = minCost;
        }
    }
    return dp[1][c-2];
}


int cost(int n, int c, vector<int> &cuts){
    
    sort(cuts.begin(), cuts.end());
   
   // adding length of bar at the end of cuts
    cuts.push_back(n);
    // adding starting point at 0th index of cuts array
    cuts.insert(cuts.begin(), 0);

//     // recursive sol
//    return solve1(cuts, 1, c);

//     // memoization sol
//     memset(dp, -1, sizeof(dp));
//    return solve2(cuts, 1, c);

    // bottom up sol
   return solve3(cuts);

}

int main(){
     vector<int> cuts = {1,3,4};
    int n=5;
    int c=cuts.size();
    cout<<cost(n, c, cuts)<<endl;
    return 0;
}