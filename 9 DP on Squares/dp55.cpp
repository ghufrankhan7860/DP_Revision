// Problem statement
// You are given an 'N' * 'M' sized binary-valued matrix 'MAT, where 'N' is the number of rows and 'M' is the number of columns. You need to return the maximum size (area) of the submatrix which consists of all 1’s i.e. the maximum area of a submatrix in which each cell has only the value ‘1’.

#include <bits/stdc++.h>
using namespace std;

// this function uses monotonic stack and calculates the maximum area of the histogram
int findMaxArea(vector<int> &histo){
    int n=histo.size();
    stack<int> st;

    int maxA=0;
    for(int i=0; i<=n; i++){
        while(!st.empty() && (i==n || histo[st.top()]>=histo[i])){
            int height = histo[st.top()];
            st.pop();
            int width;
            if(st.empty())  width = i;
            else   width = i-st.top()-1;
            maxA = max(maxA, height*width);
        }
        st.push(i);
    }
    return maxA;
}

int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &mat, int n, int m){

	vector<int> histo(m, 0);
	int maxA=0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(mat[i][j]==0){
				histo[j] = 0;
			}
			else{
				histo[j] +=mat[i][j];
			}
		}
		maxA= max(maxA, findMaxArea(histo));
	}
	return maxA;
}

int main(){
    vector<vector<int>> mat = {{1,0,1,0,0},{1,0,1,1,1},{1,1,1,1,1},{1,0,0,1,0}};
    int n=mat.size();
    int m=mat[0].size();
    cout<<maximalAreaOfSubMatrixOfAll1(mat, n, m)<<endl;
    return 0;
}