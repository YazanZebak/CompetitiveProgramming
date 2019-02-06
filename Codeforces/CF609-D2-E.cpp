#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct edge {
    int from , to  , w ;
    edge(int from , int to , int w) : from(from) , to(to) , w(w) {}
    bool operator < (const edge &e) const {
        return w > e.w ;
    }
};

struct Union_Find {

    vector < int > ranks , parent ;
    Union_Find(int n) {
        ranks = parent = vector < int > (n) ;
        for(int i = 0 ; i < n ; i++) ranks[i] = 1 , parent[i] = i ;
    }

    int find_set(int u) {
        if(u == parent[u]) return u ;
        return parent[u] = find_set(parent[u]) ;
    }

    void link(int u , int v) {
        if(ranks[u] > ranks[v]) swap(u , v);
        parent[u] = v;
        if(ranks[u] == ranks[v]) ranks[v] ++ ;
    }

    bool union_set(int u , int v) {
        u = find_set(u) , v = find_set(v) ;
        if(u != v) {
            link(u , v) ;
            return true ;
        }
        return false ;
    }
};

int n , m ;
vector < edge > edge_list ;
vector < vector < pair < int , int > > > G(200500)  ;

ll Kruskal() {

    Union_Find dsu(n) ;

    priority_queue < edge > Q  ;
    for(auto e : edge_list) Q.push(e) ;

    ll mstCost = 0 ;

    while(!Q.empty()) {
        edge e = Q.top() ;
        Q.pop() ;

        if(dsu.union_set(e.from , e.to)) {
            mstCost += e.w ;
            G[e.from].push_back({e.to , e.w});
            G[e.to].push_back({e.from , e.w});
        }
    }

    return mstCost ;
}

const int maxlog = 20 , N = 200500;
int parent[N][maxlog] , maximum[N][maxlog] , L[N];

void dfs(int u , int p , int l , int d) {

    parent[u][0] = p ;
    if(p != -1) maximum[u][0] = d;
    L[u] = l ;

    for(auto e : G[u]) {
        int v = e.first , w = e.second ;
        if(v == p) continue ;
        dfs(v , u , l + 1 , w);
    }
}
void dp() {

    for(int j = 1 ; 1 << j < n ; j++) {
        for(int i = 0 ; i < n ; i++) {
            if(parent[i][j - 1] != -1) {
                maximum[i][j] = max( maximum[i][j - 1] , maximum[parent[i][j - 1]][j - 1] ) ;
                parent[i][j] = parent[parent[i][j - 1]][j - 1] ;
            }
        }
    }

}

int lca(int u , int v){

    if(L[u] < L[v]) swap(u , v) ;

    int i , log ;
    for(log = 1 ; 1 << log <= L[u] ; log++) ;
    log-- ;

    for(i = log ; i >= 0 ; i--)
         if(L[u] - (1 << i) >= L[v])
              u = parent[u][i]  ;


    if(u == v) return u ;

    for(i = log ; i >= 0 ; i--)
          if(parent[u][i] != -1 && parent[u][i] != parent[v][i])
                 u = parent[u][i] , v = parent[v][i] ;

    return parent[u][0] ;
}

int query(int u , int v){

   int log ;
   for(log = 1 ; 1 << log <= L[u] ; log++);
   log -- ;

   int mx = -1 ;
   for(int i = log ; i >= 0 ; i--)
         if(L[u] - (1 << i) >= L[v])
              mx = max(mx , maximum[u][i]) , u = parent[u][i] ;

    return mx ;
}

int main() {
    scanf("%d%d",&n,&m);

    for(int i = 0 ; i < m ; i++) {
        int u , v ;
        ll w;
        scanf("%d%d%I64d",&u,&v,&w);
        u-- , v -- ;
        edge_list.push_back(edge(u , v , w));
    }

    ll mst = Kruskal() ;

    memset(maximum , -1 , sizeof maximum) ;
    memset(parent , -1 , sizeof parent) ;

    dfs(0 , -1 , 0 , 0) ;
    dp() ;

    for(auto e : edge_list){
          int u = e.from , v = e.to ;
          ll w = e.w ;
          int lc = lca(u , v) ;
          ll mx = max( query(u , lc) , query(v , lc) ) ;
          printf("%I64d\n",mst - mx + w);
    }

    return 0;
}
