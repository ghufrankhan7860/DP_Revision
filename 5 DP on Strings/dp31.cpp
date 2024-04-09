//  Shortest Common Supersequence
// Problem statement
// Given two strings, ‘A’ and ‘B’. Return the shortest supersequence string ‘S’, containing both ‘A’ and ‘B’ as its subsequences. If there are multiple answers, return any of them.
// Note: A string 's' is a subsequence of string 't' if deleting some number of characters from 't' (possibly 0) results in the string 's'.
// For example:
// Suppose ‘A’ = “brute”, and ‘B’ = “groot”
// The shortest supersequence will be “bgruoote”. As shown below, it contains both ‘A’ and ‘B’ as subsequences.
// A   A A     A A
// b g r u o o t e
//   B B   B B B  
// It can be proved that the length of supersequence for this input cannot be less than 8. So the output will be bgruoote.
// Sample Input 1 :
// 2
// brute
// groot
// bleed
// blue
// Sample Output 1 :
// bgruoote
// bleued

#include <bits/stdc++.h>
using namespace std;

// bottom up solution
string solve3(string &a, string &b){
    int m=a.size(), n=b.size();
    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

    for(int i=m-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(a[i] ==b[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else{
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }

    int i=0, j=0;
    string ans;
    while(i<m && j<n){
        if(a[i] == b[j]){
            ans+=a[i];
            i++; j++;
        }
        else{
            if(dp[i][j+1] > dp[i+1][j]){
                ans+=b[j];
                j++;
            }
            else{
                ans+=a[i];
                i++;
            }
        }
    }
    while(i<m){
        ans+=a[i];
        i++;
    }
    while(j<n){
        ans+=b[j];
        j++;
    }
    return ans;
}

string shortestSupersequence(string a, string b)
{
	//bottom up approach
	return solve3(a, b);
}

int main(){
    string a="brute";
    string b="groot";
    cout<<shortestSupersequence(a, b)<<endl;
    return 0;
}