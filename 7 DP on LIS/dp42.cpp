#include <bits/stdc++.h>
using namespace std;

// bottom up solution
vector<int> solve3(vector<int> arr, int n){
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));

    for(int idx=n-1; idx>=0; idx--){
        for(int last=idx-1; last>=-1; last--){
            if(last == -1 || arr[last] < arr[idx] ){
                dp[last+1][idx] = 1 + dp[idx+1][idx+1];
            }
            dp[last+1][idx] = max(dp[last+1][idx], dp[last+1][idx+1]);
        }
    }

    for(auto it:dp){
        for(auto i:it)  cout<<i<<" ";
        cout<<endl;
    }
}

vector<int> printingLongestIncreasingSubsequence(vector<int> arr, int n) {
	// non optimised bottom up solution
    return solve3(arr, n);
}


int main(){
    vector<int> nums = {5,4,11,1,16,8};
    int n=nums.size();
    vector<int> res = printingLongestIncreasingSubsequence(nums, n);
    // for(auto it:res)    cout<<it<<" ";
    // cout<<endl;
    return 0;
}