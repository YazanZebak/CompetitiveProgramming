#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e5 + 10;

ll res[N] ;
int sz[N] , r[N] , a[N];
bool big[N];
vector < int > G[N];
ll tree[N];

void update(int i , ll val){
    for( ; i < N ; i += (i & (-i))) tree[i] += val;
}

ll sum(int i){
    ll ret = 0 ;
    for( ; i ; i -= (i & (-i))) ret += tree[i];
    return ret ;
}



void dfs(int u, int p){
    sz[u] = 1;
    for(auto v : G[u]){
         if(v == p) continue;
         dfs(v , u);
         sz[u] += sz[v];
    }
}


void add(int u , int p , int val){
     if(val == -1) update(r[u] , -a[u]);
     else update(r[u] , a[u]);
     for(auto v : G[u]){
           if(big[v] || v == p) continue ;
           add(v , u , val);
     }
}

void dfs(int u , int p , bool keep){

     int mx = -1 , bigChild = -1;
     for(auto v : G[u]){
          if(v == p) continue ;
          if(sz[v] > mx){
              mx = sz[v];
              bigChild = v;
          }
     }

     for(auto v : G[u]){
          if(v == bigChild || v == p) continue ;
          dfs(v , u , 0);
     }

     if(bigChild != -1)
         dfs(bigChild , u , 1) , big[bigChild] = 1 ;

     add(u , p , 1);

     res[u] = sum(r[u] - 1);

     if(bigChild != -1)
          big[bigChild] = 0;
     if(keep == 0)
          add(u , p , -1);

}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    int n ; cin >> n ;

    int root = -1 ;

    for(int i = 1 ; i <= n ; i++){
          int v ;
          cin >> v >> r[i] >> a[i] ;

          if(v == -1) {
              root = i ;
              continue ;
          }

          G[i].push_back(v);
          G[v].push_back(i);
    }

    dfs(root , -1);
    dfs(root, -1 , 0);

    for(int i = 1 ; i <= n ; i++) cout << res[i] << endl ;

    return 0 ;
}

