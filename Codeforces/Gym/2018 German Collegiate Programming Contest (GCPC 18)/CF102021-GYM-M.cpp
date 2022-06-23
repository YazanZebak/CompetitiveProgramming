/*
	Idea:
		- link each cell with it's neighbours the cost of the edge is the max between the two heights.
		- get the mst for the formed graph. 
		- for each query get the maximum edge between (u ,v) using lca 
*/

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

struct UnionFind {

    vector < int > ranks , parent ;

    UnionFind(int n) {
        ranks = parent = vector < int > (n) ;
        for(int i = 0 ; i < n ; i++) parent[i] = i , ranks[i] = 1 ;
    }

    int find_set(int node) {
        if(node == parent[node]) return node ;
        return parent[node] = find_set( parent[node] );
    }

    void link(int u , int v) {
        if(ranks[u] > ranks[v]) swap(u , v);
        parent[u] = v ;
        if(ranks[u] == ranks[v]) ranks[v]++ ;
    }

    bool union_set(int u , int v) {
        u = find_set(u) , v = find_set(v);
        if(u != v) link(u , v);
        return u != v ;
    }
};

struct edge{
    int from , to  , cost ;
    edge(){ from = to = cost = 0 ; }
    edge(int from , int to , int cost) : from(from) , to(to) , cost(cost) {}
    bool operator < (const edge &e) const {
         return cost > e.cost;
    }
};

vector < edge > edge_list ;
vector < vector < pair < int , int > > >  G(500 * 500 + 1);

void mst(int n) {
      UnionFind tree(n);
      priority_queue < edge > Q  ;
      for(auto e : edge_list) Q.push(e);
      while(!Q.empty()) {
            edge e = Q.top() ; Q.pop() ;
            if( tree.union_set(e.from , e.to) ){
                  G[e.from].push_back({e.to , e.cost});
                  G[e.to].push_back({e.from , e.cost});
            }
      }
}

int n , m , q;
vector < int > grid[501];
int di[] = {0 , 1 , 0 , -1};
int dj[] = {1 , 0 , -1 , 0};

const int N = 250001 ;
const int nlog = 20 ;
int P[N][nlog] , L[N] , dp[N][nlog];

void dfs(int u , int p , int l , int d){
     P[u][0] = p ;
     if(p != -1) dp[u][0] = d;
     L[u] = l ;
     for(auto e : G[u]){
          int v = e.first , w = e.second ;
          if(v == p) continue ;
          dfs(v , u , l + 1 , w);
     }
}

void precompute(){

    for(int j = 1 ; 1 << j < n*m ; j++){
        for(int i = 0 ; i < n*m ; i++){
            if(P[i][j - 1] != -1){
                  dp[i][j] = max(dp[i][j - 1] , dp[P[i][j - 1]][j - 1]);
                  P[i][j] = P[P[i][j - 1]][j - 1];
            }
        }
    }

}

int lca(int u , int v){

    if(L[u] < L[v]) swap(u , v);

    int i , log ;
    for(log = 1 ; 1 << log <= L[u] ; log++) ;
    log-- ;

    for(i = log ; i >= 0 ; i--)
         if(L[u] - (1 << i) >= L[v])
           u = P[u][i] ;

    if(u == v) return u ;

    for(i = log ; i >= 0 ; i--)
        if(P[u][i] != -1 && P[u][i] != P[v][i])
           u  = P[u][i] , v = P[v][i] ;

    return P[u][0];
}

int query(int u , int v){

   int log ;
   for(log = 1 ; 1 << log <= L[u] ; log++);
   log -- ;

   int mx = -1;
   for(int i = log ; i >= 0 ; i--)
         if(L[u] - (1 << i) >= L[v])
              mx = max(mx , dp[u][i]) , u = P[u][i] ;

    return mx ;
}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);


    cin >> n >> m >> q ;

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
              int x ; cin >> x ;
              grid[i].push_back(x);
        }
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            for(int k = 0 ; k < 4 ; k++){
                  if(i + di[k] < 0 || i + di[k] >= n) continue ;
                  if(j + dj[k] < 0 || j + dj[k] >= m) continue ;
                  int ti = i + di[k] , tj = j + dj[k] ;
                  int u = i * m + j , v = ti * m + tj ;
                  int cost = max(grid[i][j] , grid[ti][tj]);
                  edge_list.push_back(edge(u , v , cost));
            }
        }
    }

    mst(n * m);

    dfs(0 , -1 , 0 , 0);
    precompute();


    while(q--){
          int x1 , y1 , x2 , y2 ;
          cin >> x1 >> y1 >> x2 >> y2 ;
          x1 -- , y1-- , x2-- , y2 -- ;

          if(x1 == x2 && y1 == y2){
              cout << grid[x1][y1] << endl ;
              continue ;
          }
          int u = x1 * m + y1 , v = x2 * m + y2 ;
          int lc = lca(u , v);
          cout << max( query(u , lc) , query(v , lc))  << endl  ;
    }





	return 0;
}