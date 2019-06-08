#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
const int N = 200005;

vector < pair < int , int > > G[N];
int sub[N] , par[N];
bool blocked[N];
int n , k ;

void get_size(int u, int p){

    par[u] = p ;
    sub[u] = 1 ;

    for(auto ch : G[u]){
          int v = ch.first;
          if(v == p || blocked[v]) continue ;
          get_size(v , u);
          sub[u] += sub[v];
    }
}

set < pair < int , int > > se;

int dfs(int u , int p , ll w , int d){

    if(w > k) return n ;

    int ret = n ;

    if(w == k) ret = d;

    auto it = se.lower_bound({k - w , 0});
    if(it != se.end()){
          auto t = *it;
          if(t.first == k - w)
             ret = min(ret , d + t.second) ;
    }

    for(auto ch : G[u]){
          int v = ch.first , ww = ch.second ;
          if(v == p || blocked[v]) continue ;
          ret = min(ret , dfs(v , u , w + ww , d + 1));
    }

    return ret ;
}

void update(int u , int p , ll w , int d){

     if(w > k) return ;

     se.insert({w , d});

     for(auto ch : G[u]){
          int v = ch.first , ww = ch.second ;
          if(v == p || blocked[v]) continue ;
          update(v , u , w + ww , d + 1);
     }
}

int solve(int u){

    se.clear() ;

    int ret = n ;

    for(auto ch : G[u]){
          int v = ch.first , w = ch.second ;
          if(blocked[v]) continue ;
          ret = min(ret , dfs(v , u , w , 1));
          update(v , u , w , 1);
    }

    return ret;
}

int get_centroid(int src){

    get_size(src , src);

    queue < int > Q ;
    Q.push(src);

    int centroid = src , best = sub[src];

    while(!Q.empty()){
          int u = Q.front();
          Q.pop();

          int size = sub[src] - sub[u];
          for(auto ch : G[u]){
              int v = ch.first;
              if(v == par[u] || blocked[v]) continue ;
              Q.push(v);
              size = max(size , sub[v]);
          }

          if(best > size){
               best = size ;
               centroid = u ;
          }
    }

    blocked[centroid] = true ;

    int ret = solve(centroid);

    for(auto ch : G[centroid]){
          int v = ch.first;
          if(blocked[v]) continue ;
          ret = min(ret , get_centroid(v));
    }

    return ret;
}


int best_path(int nn , int kk , int H[][2] , int L[]) {

    n = nn ;
    k = kk ;

    vector < pair < int , int > > ve ;

    for(int i = 0 ; i < n - 1 ; i++){
          int u , v , w ;
          u = H[i][0] , v =  H[i][1] , w = L[i];
          G[u].push_back({v , w});
          G[v].push_back({u , w});
    }

    int ans = get_centroid(0);

    if(ans == n) ans = -1 ;

    return ans;
}
