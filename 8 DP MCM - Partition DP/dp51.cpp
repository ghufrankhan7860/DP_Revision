// Problem statement
// You are given an array 'arr' of 'n' balloons, where 'a[i]' represents the coins associated with 'ith' balloon.
// On bursting 'ith' balloon, the number of coins collected is equal to 'a[i-1] * a[i] * a[i+1]'. Also, balloons 'i-1' and 'i+1' now become adjacent.
// Find the maximum possible coins collected after bursting all the balloons. Assume an extra 1 at each boundary.
// Example:
// Input: 'arr' = [5,2,6,9]
// Output: 384
// Explanation:
// The best way to burst balloons is following:
// Choosing 2nd balloon, we get 5*2*6 coins. Now the array is [5,6,9].
// Choosing 2nd balloon, we get 5*6*9 coins. Now the array is [5,9].
// Choosing 1st balloon, we get 1*5*9 coins. Now the array is [9].
// Choosing the last balloon, we get 1*9*1 coins.
// Finally we get 5*2*6 + 5*6*9 + 1*5*9 + 1*9*1 = 384 coins.
// There's no way to choose the order of bursting balloons such that we get more than 384 coins.
// Detailed explanation ( Input/output format, Notes, Images )
// Sample Input 1:
// 2  
// 5 10
// Sample Output 1:
// 60 
// Explanation of Sample Input 1:
// For the given input, best way to burst balloons is as follows:
// First burst the 1st balloon collecting coins = 1*5*10. Now the array becomes [10].
// Then burst the last remaining balloon collecting coins = 1*10*1.  
// Finally total number of coins collected = 1*5*10 + 1*10*10 = 60.
// Sample Input 2:
// 4  
// 1 2 3 4
// Sample Output 2:
// 40 
// Expected Time Complexity:
// Try to solve this in O(n^3).
// Constraints:
// 1 ≤ n ≤ 100
// 0 ≤ arr[i] ≤ 100


#include <bits/stdc++.h>
using namespace std;

// recursive sol
int solve1(vector<int> &arr, int i, int j){

    if(i>j) return 0;
    int maxProfit=INT_MIN;
    for(int idx=i; idx<=j; idx++){
        maxProfit = max(maxProfit, (arr[i-1] *arr[idx] * arr[j+1] ) + solve1(arr, i, idx-1) + solve1(arr, idx+1, j));
    }
    return maxProfit;
}
// memoization sol
int dp[103][103];
int solve2(vector<int> &arr, int i, int j){

    if(i>j) return 0;
    int maxProfit=INT_MIN;
    for(int idx=i; idx<=j; idx++){
        maxProfit = max(maxProfit, (arr[i-1] *arr[idx] * arr[j+1] ) + solve2(arr, i, idx-1) + solve2(arr, idx+1, j));
    }
    return maxProfit;
}

//bottom up
int solve3(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i=n-2; i>=1; i--){
        for(int j=i; j<=n-2; j++){
            int maxProfit = 0;
            for(int idx=i; idx<=j; idx++){
                maxProfit = max(maxProfit, arr[i-1]*arr[idx]*arr[j+1] + dp[i][idx-1] + dp[idx+1][j]);
            }
            dp[i][j] = maxProfit;
        }
    }
    return dp[1][n-2];
}

int burstBalloons(vector<int> &arr){
    int n=arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(), 1);

    // // recursive sol
    // return solve1(arr, 1, n);

    // // memoization sol
    // memset(dp, -1, sizeof(dp));
    // return solve2(arr, 1, n);

    // bottom up
    return solve3(arr);
}

int main(){
    vector<int> arr= {7,1,8};
    cout<<burstBalloons(arr)<<endl;
    return 0;
}