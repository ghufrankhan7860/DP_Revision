//  Longest String Chain
// Problem statement
// You are given an array 'arr' of strings, where each string consists of English lowercase letters.
// A string chain of 'arr' is defined as:
// (1) A sequence of string formed using elements of 'arr'.
// (2) Every string in the sequence can be formed by inserting a lowercase English letter into the previous string (except the first string).
// Find the length of the longest possible string chain of 'arr'.
// Example :
// Input: 'arr' = ["x", "xx", "y", "xyx"] 
// Output: 3

#include <bits/stdc++.h>
using namespace std;

// used to sort in increasing length of string 
bool comp(string &s1, string &s2){
    return s1.size()<s2.size();
}

bool check(string &s1, string &s2){
    int n1=s1.size();
    int n2=s2.size();
    if(n1==n2+1){
        int i=0, j=0;
        while(i<n1){
            if(s1[i] == s2[j])  {
                i++; j++;
            }
            else{
                i++;
            }
        }
        if(i==n1 && j==n2)   return true;
    }
    return false;

}

// bottom up solution
int solve1(vector<string> &arr){
    int n=arr.size();
    vector<int> dp(n, 1);

    int maxChainLen=1;
    sort(arr.begin(), arr.end(), comp);
    for(int i=1; i<n; i++){
        for(int j=0; j<n; j++){
            if(check(arr[i], arr[j]) && dp[i]< dp[j] + 1 ){
                dp[i] = dp[j] + 1;
                maxChainLen = max(maxChainLen, dp[i]);
            }
        }
    }
    return maxChainLen;
    
}

int longestStrChain(vector<string> &arr){
    // bottomup solution
    return solve1(arr);
}

int main(){
    vector<string> arr= {"x","xx","y","xyx", "yx", "zyx", "zydx"};
    cout<<longestStrChain(arr)<<endl;
    return 0;
}