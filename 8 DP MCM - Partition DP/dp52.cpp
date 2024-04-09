// Problem statement
// You are given an expression 'exp' in the form of a string where operands will be : (TRUE or FALSE), and operators will be : (AND, OR or XOR).
// Now you have to find the number of ways we can parenthesize the expression such that it will evaluate to TRUE.
// As the answer can be very large, return the output modulo 1000000007.
// Note :
// ‘T’ will represent the operand TRUE.
// ‘F’ will represent the operand FALSE.
// ‘|’ will represent the operator OR.
// ‘&’ will represent the operator AND.
// ‘^’ will represent the operator XOR.
// Example :
// Input: 'exp’ = "T|T & F".
// Output: 1


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int mod = 1e9+7;

// recursive sol
ll solve1(string &exp, int i, int j, int isTrue){
    if(i>j) return 0;

    if(i==j){
        if(exp[i]=='T') return (isTrue==1);
        else    return (isTrue == 0);
    }

    ll ways = 0;
    for(int idx=i+1; idx<j; idx+=2){
        ll lt = solve1(exp, i, idx-1, 1);
        ll lf = solve1(exp, i, idx-1, 0);
        ll rt = solve1(exp, idx+1, j, 1);
        ll rf = solve1(exp, idx+1, j, 0);

        if(exp[idx] == '&'){
            if(isTrue)
                ways = (ways + lt*rt)%mod;
            else
                ways = ((ways + lt*rf)%mod + (lf*rt + lf*rf)%mod)%mod;
        }
        else if(exp[idx] == '^'){
            if(isTrue)
                ways = ((ways + lf*rt)%mod + lt*rf)%mod;
            else ways = ((ways + lt*rt)%mod + lf*rf)%mod; 
        }
        else{
            if(isTrue)
                ways = ((ways + lt*rt)%mod + (lf*rt + lt*rf)%mod)%mod;
            else ways = (ways + lf*rf)%mod;
        }
    }
    return ways;
}

// memoization sol
int dp[201][201][2];
ll solve2(string &exp, int i, int j, int isTrue){
    if(i>j) return 0;

    if(i==j){
        if(exp[i]=='T') return (isTrue==1);
        else    return (isTrue == 0);
    }

    if(dp[i][j][isTrue] != -1)  return dp[i][j][isTrue];

    ll ways = 0;
    for(int idx=i+1; idx<j; idx+=2){
        ll lt = solve2(exp, i, idx-1, 1);
        ll lf = solve2(exp, i, idx-1, 0);
        ll rt = solve2(exp, idx+1, j, 1);
        ll rf = solve2(exp, idx+1, j, 0);

        if(exp[idx] == '&'){
            if(isTrue)
                ways = (ways + lt*rt)%mod;
            else
                ways = ((ways + lt*rf)%mod + (lf*rt + lf*rf)%mod)%mod;
        }
        else if(exp[idx] == '^'){
            if(isTrue)
                ways = ((ways + lf*rt)%mod + lt*rf)%mod;
            else ways = ((ways + lt*rt)%mod + lf*rf)%mod; 
        }
        else{
            if(isTrue)
                ways = ((ways + lt*rt)%mod + (lf*rt + lt*rf)%mod)%mod;
            else ways = (ways + lf*rf)%mod;
        }
    }
    return dp[i][j][isTrue] = ways;
}

// bottom up 
ll solve3(string &exp, int n){
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(n+1, vector<int>(2, 0)));

    for(int i=n-1; i>=0; i--){
        for(int j=i; j<n; j++){
            for(int isTrue = 0; isTrue<=1; isTrue++){
                if(i==j){
                    if(exp[i]=='T')
                        dp[i][j][isTrue]   = (isTrue == 1);
                    else dp[i][j][isTrue]  = (isTrue == 0);
                    continue;
                }
                
                ll ways = 0;
                for(int idx=i+1; idx<j; idx+=2){
                    ll lt = dp[i][idx-1][1];
                    ll lf = dp[i][idx-1][0];
                    ll rt = dp[idx+1][j][1];
                    ll rf = dp[idx+1][j][0];

                    if(exp[idx] == '&'){
                        if(isTrue)
                            ways = (ways + lt*rt)%mod;
                        else
                            ways = ((ways + lt*rf)%mod + (lf*rt + lf*rf)%mod)%mod;
                    }
                    else if(exp[idx] == '^'){
                        if(isTrue)
                            ways = ((ways + lf*rt)%mod + lt*rf)%mod;
                        else ways = ((ways + lt*rt)%mod + lf*rf)%mod; 
                    }
                    else{
                        if(isTrue)
                            ways = ((ways + lt*rt)%mod + (lf*rt + lt*rf)%mod)%mod;
                        else ways = (ways + lf*rf)%mod;
                    }
                }
                dp[i][j][isTrue] = ways;
            }
        }
    }
    return dp[0][n-1][1];
}

int evaluateExp(string & exp) {
    int n=exp.size();

//    // recursive sol
//    return solve1(exp, 0, n-1, 1);
   
//    // memoization sol
//    memset(dp, -1, sizeof(dp));
//    return solve2(exp, 0, n-1, 1);

   // bottom up solution
   return solve3(exp, n);
}

int main(){
    string expression = "T&F|T^F";
    cout<<evaluateExp(expression)<<endl;
    return 0;
}