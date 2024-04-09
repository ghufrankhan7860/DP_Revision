// Problem statement
// A matrix 'arr' with 'n' rows and 'm' columns is given.
// Count the number of square submatrices in matrix ‘arr’ with all elements equal to 1.
// A square matrix is a matrix with square dimensions.
// Example :
// Input: If 'n' = 2, 'm' = 2, and 'arr' = [ [1, 1], [1, 1] ].
// Output: 5
// Explanation: We have 4 square submatrices of size 1*1 and 1 square submatrix of size 2*2. 

#include <bits/stdc++.h>
using namespace std;

// tabulation method
int countSquares(int n, int m, vector<vector<int>> &arr) {
    vector<vector<int>> dp(n, vector<int>(m,0));

    // copying first row of arr in dp row
    dp[0] = arr[0];

    // copying first column of arr in dp first arr
    for(int i=1; i<n; i++)  dp[i][0] = arr[i][0];

    for(int i=1; i<n; i++){
        for(int j=1; j<m; j++){
            if(arr[i][j]){
                dp[i][j] = 1 + min(dp[i][j-1], min(dp[i-1][j], dp[i-1][j-1]));
            }
        }
    }

    int ans=0;
    // summing the dp array
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ans += dp[i][j];
        }
    }
    return ans;
}


int main(){
    vector<vector<int>> arr = {{1,1,1,1,0},{1,1,0,0,1},{1,1,1,0,0},{1,1,1,1,0}};
    int n=arr.size();
    int m=arr[0].size();
    cout<<countSquares(n, m, arr)<<endl;
    return 0;
}