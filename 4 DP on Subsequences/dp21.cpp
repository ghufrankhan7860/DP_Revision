// Target Sum
// Problem statement
// You are given an array ‘ARR’ of ‘N’ integers and a target number, ‘TARGET’. Your task is to build an expression out of an array by adding one of the symbols '+' and '-' before each integer in an array, and then by concatenating all the integers, you want to achieve a target. You have to return the number of ways the target can be achieved.

// For Example :
// You are given the array ‘ARR’ = [1, 1, 1, 1, 1], ‘TARGET’ = 3. The number of ways this target can be achieved is:
// 1. -1 + 1 + 1 + 1 + 1 = 3
// 2. +1 - 1 + 1 + 1 + 1 = 3
// 3. +1 + 1 - 1 + 1 + 1 = 3
// 4. +1 + 1 + 1 - 1 + 1 = 3
// 5. +1 + 1 + 1 + 1 - 1 = 3
// These are the 5 ways to make. Hence the answer is 5.


#include <bits/stdc++.h>
using namespace std;

// bottom up sol
int solve3(int n, int tar, vector<int> &arr){

    int totalSum=0;
    for(auto it:arr)    totalSum += it;

    vector<vector<int>> dp(n+1, vector<int>(totalSum+1, 0));

    // base case
    for(int i=0; i<=n; i++) dp[i][0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        for(int k = 1; k<=totalSum; k++){
            if(k>=arr[idx])
                dp[idx][k] = dp[idx+1][k-arr[idx]];
            dp[idx][k] = dp[idx][k] + dp[idx+1][k];
        }
    }

    int count = 0;
    for(int j=0; j<=totalSum; j++){
        if(j-(totalSum-j) == tar)
            count += dp[0][j];
    }

    return count;
}

int solve4(int n, int tar, vector<int> &arr){

    int totalSum=0;
    for(auto it:arr)    totalSum += it;

    vector<int> prev(totalSum+1, 0), curr(totalSum+1, 0);

    // base case
    prev[0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        curr[0] = 1;
        for(int k = 1; k<=totalSum; k++){
            if(k>=arr[idx])
                curr[k] = prev[k-arr[idx]];
            curr[k] = curr[k] + prev[k];
        }
        prev = curr;
    }

    int count = 0;
    for(int j=0; j<=totalSum; j++){
        if(j-(totalSum-j) == tar)
            count += prev[j];
    }

    return count;
}

int targetSum(int n, int target, vector<int>& arr) {

//    // using dp 18 function same
//    sort(arr.begin(), arr.end());
//    return solve3(n , target, arr);


    // using dp 18 function same
    sort(arr.begin(), arr.end());
    return solve4(n , target, arr);

}


int main(){
    
    return 0;
}