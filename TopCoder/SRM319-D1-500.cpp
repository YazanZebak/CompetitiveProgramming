/*
	Idea:
	    - we can reformulate the problem to:
	    - how many ways can you insert a series of values into a BST to form a specific tree 
		- a brief explanation for the solution: https://stackoverflow.com/a/17119117/7551287
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 27 ;
int subTree[N];
vector < int > ve;
unordered_map < ll , bool > vis ;

ll C[N][N] ;
void build() {
    for(int i = 0 ; i < N  ; i++)
        for(int j = 0 ; j < N  ; j++)
            C[i][j] = (j == 0 ? 1 : ((i == 0) ? 0 : C[i - 1][j - 1] + C[i - 1][j]));
}

int idx(int n){
    return lower_bound(ve.begin() , ve.end() , n) - ve.begin();
}

ll dfs(int u) {
    int v = idx(u);
    subTree[v] = 1 ;

    ll c1 = 0 ,  c2 = 0 , resl = 1 , resr = 1 ;

    if(vis[2 * u]){
            resl = dfs(2 * u) ;
            int l = idx(2 * u);
            subTree[v] += subTree[l] ;
            c1 = subTree[l] ;
    }
    if(vis[2 * u + 1]){
            resr = dfs(2 * u + 1);
            int r = idx(2 * u + 1) ;
            subTree[v] += subTree[r] ;
            c2 = subTree[r];
    }

    return C[c1 + c2][c1] * resl * resr ;
}



class ConstructBST {

public :
    ll numInputs(vector < int > tree) {
        sort(tree.begin() , tree.end());
        ve = tree ;
        for(auto i : tree) vis[i] = 1;
        build();
        return dfs(1) ;
    }
};
