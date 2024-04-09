// Divisible Set
// Problem statement
// You are given an array of distinct numbers ‘arr’ of size 'n'.
// Your task is to return the largest subset of numbers from ‘arr’, such that any pair of numbers ‘a’ and ‘b’ from the subset satisfies the following: a % b == 0 or b % a == 0.
// A subset is nothing but any possible combination of the original array
// Example:
// Input: ‘arr’ = [1, 16, 7, 8, 4]
// Output: [1, 4, 8, 16].
// Explanation: In the set {1, 4, 8, 16}, you can take any pair from the set, and either one of the elements from the pair will divide the other.
// There are other possible sets, but this is the largest one.

#include <bits/stdc++.h>
using namespace std;

vector<int> solve1(vector<int> &arr){
    int n=arr.size();
    sort(arr.begin(), arr.end());

    vector<int> dp(n, 1);
    vector<int> hash(n, -1);
    
    int maxSubsetLen=1, last=0;
    for(int i=1; i<n; i++){
        for (int j = 0; j < i; j++)
        {
            if(arr[i]%arr[j]==0 && dp[i] < dp[j] +1 ){
                dp[i] = dp[j] +1 ;
                hash[i] = j;

                if(maxSubsetLen < dp[i]){
                    maxSubsetLen = max(maxSubsetLen, dp[i]);
                    last = i;
                }
            }
        }
    }
    vector<int> res(maxSubsetLen);
    for(int i=maxSubsetLen-1; i>=0; i--){
        res[i] = arr[last];
        last=hash[last];
    }
    return res;
}


vector<int> divisibleSet(vector<int> &arr)
{
    // bottom up solution
    return solve1(arr);
}
int main(){
    // vector<int> arr = {1,16,7,8,4};
    vector<int> arr = {24,9,20,9,9,11,20};
    vector<int> res = divisibleSet(arr);
    for(auto it:res)    cout<<it<<" ";
    cout<<endl;
    return 0;
}