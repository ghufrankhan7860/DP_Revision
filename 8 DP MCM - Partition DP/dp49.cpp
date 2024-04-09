// Problem statement
// Given a chain of matrices A1, A2, A3,.....An, you have to figure out the most efficient way to multiply these matrices. In other words, determine where to place parentheses to minimize the number of multiplications.
// You will be given an array p[] of size n + 1. Dimension of matrix Ai is p[i - 1]*p[i]. You need to find minimum number of multiplications needed to multiply the chain.
// Sample Input:
// 3
// 10 15 20 25
// Sample Output:
// 8000

#include <bits/stdc++.h>
using namespace std;

//bottom up
int solve3(int *arr, int n){
    vector<vector<int>> dp(n+2, vector<int> (n+2, 1e9));

    for(int i=0; i<=n; i++)  dp[i][i] = 0;

    for(int i=n; i>=1; i--){
        for(int j=i+1; j<=n; j++){
            int count = 1e9;
            for(int idx=i; idx<j; idx++){
                count = min(count, arr[i-1] * arr[idx] * arr[j] + dp[i][idx] + dp[idx+1][j]);
            }
            dp[i][j] = count;
        }
    }
    return dp[1][n];
}

int matrixChainMultiplication(int* arr, int n) {
    // bottom up 
    return solve3(arr, n);
}
int main(){
    vector<int> nums={10,15,20,25};
    int n=nums.size();
    int *arr= new int[n];
    for(int i=0; i<n; i++)  arr[i] = nums[i];
    n--;
    cout<<matrixChainMultiplication(arr, n)<<endl;
    return 0;
}