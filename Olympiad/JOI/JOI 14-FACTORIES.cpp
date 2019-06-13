#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
const int N = 5 * 1e5 + 1 ;
const ll inf = 1e18 ;
 
vector < pair < int, int > > G[N];
int sub[N], p[N] , par[N];
bitset < N > blocked;
 
void get_size(int u, int pa) {
    p[u] = pa ;
    sub[u] = 1 ;
    for(auto e : G[u]) {
        int v = e.first ;
        if(blocked[v] || v == pa) continue ;
        get_size(v, u);
        sub[u] += sub[v];
    }
}
 
vector < ll > dis[N];
 
void solve(int u , int p , ll d){
     for(auto e : G[u]){
          int v = e.first , w = e.second ;
          if(blocked[v] || v == p) continue ;
          dis[v].emplace_back(d + w);
          solve(v , u , d + w);
     }
}
 
int get_centroid(int src) {
 
    get_size(src, src);
 
    int centroid = src, best = sub[src] ;
    queue < int > Q ;
    Q.emplace(src);
 
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
 
        int size = sub[src] - sub[u];
        for(auto e : G[u]) {
            int v = e.first;
            if(blocked[v] || v == p[u])
                continue ;
            Q.emplace(v);
            size = max(size, sub[v]);
        }
 
        if(best > size) {
            best = size;
            centroid = u ;
        }
    }
 
    blocked[centroid] = true;
 
    solve(centroid , centroid , 0);
 
    for(auto e : G[centroid]) {
        int v = e.first ;
        if(blocked[v]) continue ;
        int child = get_centroid(v);
        par[child] = centroid ;
    }
 
    return centroid ;
}
 
ll ans[N];
int vis[N];
int t = 1 ;
 
inline void update(int &u) {
    int v = u ;
    int i = dis[u].size() - 1;
    while(true) {
        if(vis[v] != t)
            vis[v] = t , ans[v] = inf ;
        ans[v] = min(ans[v], dis[u][i]);
        if(v == par[v]) break ;
        v = par[v];
        i--;
    }
}
 
inline ll query(int &u) {
    int v = u;
    ll ret = inf ;
    int i = dis[u].size() - 1 ;
    while(true) {
        if(vis[v] != t)
            vis[v] = t , ans[v] = inf ;
        ret = min(ret, ans[v] + dis[u][i]);
        if(v == par[v]) break ;
        v = par[v];
        i-- ;
    }
    return ret;
}
 
 
ll Query(int S, int X[N], int T, int Y[N]) {
 
    t++ ;
 
    for(int i = 0 ; i < T ; i++) {
        update(Y[i]);
    }
 
    ll ret = inf ;
    for(int i = 0 ; i < S ; i++) {
        ret = min(ret,  query(X[i]));
    }
 
    return ret;
}
 
void Init(int n , int A[N], int B[N], int D[N]) {
 
 
    for(int i = 0 ; i < n - 1 ; i++) {
        int u = A[i], v = B[i], w = D[i];
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
 
    int root = get_centroid(0);
    par[root] = root;
 
    for(int i = 0 ; i < n ; i++) dis[i].emplace_back(0);
}
 