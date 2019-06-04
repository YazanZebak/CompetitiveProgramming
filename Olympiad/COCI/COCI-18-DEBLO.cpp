#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 10 ;
int A[N];
int n ;
vector < int > G[N];

int sub[N] , par[N];
bool blocked[N];

void get_size(int u , int p){
     sub[u] = 1 ;
     par[u] = p ;
     for(auto v : G[u]){
          if(v == p || blocked[v]) continue ;
          get_size(v , u);
          sub[u] += sub[v];
     }
}

ll cnt[40][2];

ll dfs(int u , int p , int d , int diff){

   ll ret = d ;

   for(int i = 0 ; i < 25 ; i++){
        bool bit = (d ^ diff) & (1 << i);
        ret += (cnt[i][!bit] * (1LL << i));
   }

   for(auto v : G[u]){
        if(v == p || blocked[v]) continue ;
        ret += dfs(v , u , d ^ A[v] , diff);
   }

   return ret;
}


void update(int u , int p , int d){

    for(int i = 0 ; i < 25 ; i++){
          bool bit = d & (1 << i);
          cnt[i][bit]++;
    }

    for(auto v : G[u]){
          if(v == p || blocked[v]) continue;
          update(v , u , d ^ A[v]);
    }

}


ll solve(int u){

    memset(cnt , 0 , sizeof cnt);

    ll ret = A[u];

    for(auto v : G[u]){
          if(blocked[v]) continue ;
          ret += dfs(v , u , A[v] ^ A[u] , A[u]);
          update(v , u , A[v] ^ A[u]);
    }

    return ret;
}


ll get_centroid(int src){

    get_size(src , src);

    queue < int > Q;
    Q.push(src);
    int centroid = src , best = sub[src] ;
    while(!Q.empty()){
           int u = Q.front();
           Q.pop() ;

           int size = sub[src] - sub[u];
           for(auto v : G[u]){
               if(v == par[u] || blocked[v]) continue ;
               Q.push(v);
               size = max(size , sub[v]);
           }

           if(best > size){
               best = size ;
               centroid = u ;
           }
    }

    blocked[centroid] = true;

    ll ret = solve(centroid);

    for(auto v : G[centroid]){
          if(blocked[v]) continue;
          ret += get_centroid(v);
    }


    return ret ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    for(int i = 1 ; i <= n ; i++){
          cin >> A[i];
    }

    for(int i = 0 ; i < n - 1 ; i++){
          int u , v ;
          cin >> u >> v ;
          G[u].push_back(v);
          G[v].push_back(u);
    }

    cout << get_centroid(1) << endl ;

    return 0;
}
