#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 10 ;
const int logN = 20 ;
vector < int > G[N] ;
int in[N] , out[N] , L[N] , P[N][logN] , par[N] ;
vector < int > level[N];
int timer = 1 ;

void dfs(int u , int p , int l){
    L[u] = l ;
    P[u][0] = p ;
    in[u] = timer++ ;
    level[l].push_back(in[u]);

    for(auto v : G[u]){
          if(v == p) continue ;
          dfs(v , u , l + 1) ;
    }

    out[u] = timer - 1 ;
}

int query(int u , int dist){

    for(int i = logN - 1 ; i >= 0 ; i--)
        if(dist & (1 << i))
           u = P[u][i] ;

    return u ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    int n ; cin >> n ;

    for(int i = 1; i <= n ; i++){
         int x ; cin >> x ;
         if(!x) continue ;

         G[x].push_back(i);
         G[i].push_back(x);
         par[i] = x;
    }

    for(int i = 1; i <= n ; i++)
        if(par[i] == 0)
            dfs(i , 0 , 0) ;

    for(int j = 1 ; j < logN ; j++)
        for(int i = 1 ; i <= n ; i++)
            P[i][j] = P[P[i][j - 1]][j - 1] ;

    int q ; cin >> q ;

    while(q--){
         int u , h ;
         cin >> u >> h ;
         int v = query(u , h) ;

         if(!v) {
              cout << "0" << " " ;
              continue ;
         }

         int res = upper_bound(level[L[u]].begin() , level[L[u]].end() , out[v]) -
                   lower_bound(level[L[u]].begin() , level[L[u]].end() , in[v]) ;

         cout << res - 1 << " " ;
    }

    return 0;
}