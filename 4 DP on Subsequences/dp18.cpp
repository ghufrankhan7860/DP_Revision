// Partitions With Given Difference
// Problem statement
// Given an array ‘ARR’, partition it into two subsets (possibly empty) such that their union is the original array. Let the sum of the elements of these two subsets be ‘S1’ and ‘S2’.
// Given a difference ‘D’, count the number of partitions in which ‘S1’ is greater than or equal to ‘S2’ and the difference between ‘S1’ and ‘S2’ is equal to ‘D’. Since the answer may be too large, return it modulo ‘10^9 + 7’.
// If ‘Pi_Sj’ denotes the Subset ‘j’ for Partition ‘i’. Then, two partitions P1 and P2 are considered different if:
// 1) P1_S1 != P2_S1 i.e, at least one of the elements of P1_S1 is different from P2_S2.
// 2) P1_S1 == P2_S2, but the indices set represented by P1_S1 is not equal to the indices set of P2_S2. Here, the indices set of P1_S1 is formed by taking the indices of the elements from which the subset is formed.
// Refer to the example below for clarification.
// Note that the sum of the elements of an empty subset is 0.
// For example :
// If N = 4, D = 3, ARR = {5, 2, 5, 1}
// There are only two possible partitions of this array.
// Partition 1: {5, 2, 1}, {5}. The subset difference between subset sum is: (5 + 2 + 1) - (5) = 3
// Partition 2: {5, 2, 1}, {5}. The subset difference between subset sum is: (5 + 2 + 1) - (5) = 3
// These two partitions are different because, in the 1st partition, S1 contains 5 from index 0, and in the 2nd partition, S1 contains 5 from index 2.


#include <bits/stdc++.h>
using namespace std;

int mod = 1e9+7;

// bottom up solution
int solve3(int n, int tar, vector<int> &arr, int d){
    vector<vector<int>> dp(n+1, vector<int>(tar+1, 0));

    // base case
    for(int i=0; i<=n; i++) dp[i][0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        for(int k=0; k<=tar; k++){
            
            int take = 0, skip = 0;

            if(arr[idx] <= k){
                take = dp[idx+1][k-arr[idx]];
            }

            skip = dp[idx+1][k];
            
            dp[idx][k] = (take + skip)%mod;
        }
    }

    int count = 0;
    for(int i=tar/2; i<=tar; i++){
        if((i-(tar-i)) == d) count+=dp[0][i];
    }
    return count;
}

// bottom up solution->space optimisation
int solve4(int n, int tar, vector<int> &arr, int d){
    vector<int> prev(tar+1, 0), curr(tar+1, 0);

    // base case
    prev[0] = 1;

    for(int idx=n-1; idx>=0; idx--){
        curr[0]=1;
        for(int k=0; k<=tar; k++){
            
            int take = 0, skip = 0;

            if(arr[idx] <= k){
                take = prev[k-arr[idx]];
            }

            skip = prev[k];
            
            curr[k] = (take + skip)%mod;
        }
        prev=curr;
    }
    int count = 0;
    for(int i=tar/2; i<=tar; i++){
        if((i-(tar-i)) == d) count+=prev[i];
    }
    return count;
}

int countPartitions(int n, int d, vector<int> &arr) {
    int tar= 0;
    for(auto it:arr)    tar += it;

    // bottom up solution
    return solve3(n, tar, arr, d);

    // bottom up solution->space optimisation
    return solve4(n, tar, arr, d);
}

int main(){
    vector<int> arr ={4,6,3};
    int n = arr.size();
    int d = 1;
    cout<<countPartitions(n, d, arr)<<endl;
    return 0;
}