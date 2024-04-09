// Longest Bitonic Sequence
// Problem statement
// A Bitonic Sequence is a sequence of numbers that is first strictly increasing and then strictly decreasing.
// A strictly ascending order sequence is also considered bitonic, with the decreasing part as empty, and same for a strictly descending order sequence.
// For example, the sequences [1, 3, 5, 3, 2], [1, 2, 3, 4] are bitonic, whereas the sequences [5, 4, 1, 4, 5] and [1, 2, 2, 3] are not.
// You are given an array 'arr' consisting of 'n' positive integers.
// Find the length of the longest bitonic subsequence of 'arr'.
// Example :
// Input: 'arr' = [1, 2, 1, 2, 1]
// Output: 3


#include <bits/stdc++.h>
using namespace std;

// bottom up solution
int solve(vector<int> &arr, int n){
    vector<int> dp1(n, 1), dp2(n, 1);

    for(int i=1; i<n; i++){
        for(int j=0; j<i; j++){
            if(arr[i] > arr[j] && (dp1[j]+1 > dp1[i])){
                dp1[i] = dp1[j]+1;
            }
        }
    }

    for(int i=n-2; i>=0; i--){
        for(int j=i+1; j<n; j++){
            if(arr[i] > arr[j] && (dp2[j]+1 > dp2[i])){
                dp2[i] = dp2[j]+1;
            }
        }
    }

    for(auto it:dp1)    cout<<it<<" ";
    cout<<endl;
    for(auto it:dp2)    cout<<it<<" ";
    cout<<endl;

    int maxlenBitonicSeqSize = 0;
    for(int i=0; i<n; i++){
        maxlenBitonicSeqSize = max(maxlenBitonicSeqSize, dp1[i]+dp2[i]-1);
    }
    return maxlenBitonicSeqSize;

}

int longestBitonicSubsequence(vector<int>& arr, int n)
{
	return solve(arr, n);
}


int main(){
    // vector<int> arr={1,11,2,10,4,5,2,1};
    vector<int> arr={1,2,1,2,1};
    int n=arr.size();

    cout<<longestBitonicSubsequence(arr, n)<<endl;

    return 0;
}