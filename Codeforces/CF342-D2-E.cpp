#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
const int N = 100500 ;
const int nlog = 21 ;

int n , q ;
int P[N][nlog] , L[N] ;
vector < vector < int > > tree(N) ;

void dfs(int u , int p , int l){

     P[u][0] = p ;
     L[u] = l ;
     for(auto v : tree[u]){
          if(v == p) continue ;
          dfs(v , u , l + 1) ;
     }
}
void dp(){

    memset(P , -1 , sizeof P) ;
    memset(L , 0 , sizeof L) ;

    dfs(0 , -1 , 0) ;


    for(int j = 1 ;  1 << j < n ; j++)
        for(int i = 0 ; i < n ; i++)
           if(P[i][j - 1] != -1)
             P[i][j] = P[P[i][j - 1]][j - 1];
}

int lca(int u , int v){

    if(L[u] < L[v])
          swap(u , v) ;

    int log ;

    for(log = 1 ; (1 << log) <= L[u] ; log++) ;

    --log ;


    for(int i = log ; i >= 0 ; i--){
          if(L[u] - (1 << i) >= L[v]){

              u = P[u][i] ;
          }
    }

    if(u == v)
       return u ;

    for(int i = log ; i >= 0 ; i--)
          if(P[u][i] != -1 && P[u][i] != P[v][i])
              u = P[u][i] , v = P[v][i] ;

    return P[u][0];
}

int calc(int u , int v){
    return L[u] + L[v] - 2 * L[lca(u , v)] ;
}

vector < int > bfs(vector < int > src){

     const int inf = 1 << 30 ;
     vector < int > dist(n + 1 , inf) ;
     queue < int > Q ;

     for(auto i : src){
           dist[i] = 0 ;
           Q.push(i);
     }

     while(!Q.empty()){
           auto p = Q.front() ;
           Q.pop() ;
           int u = p ;
           for(auto v : tree[u]){
                if(dist[v] > dist[u] + 1){
                      dist[v] = dist[u] + 1 ;
                      Q.push(v);
                }
           }
     }

     return dist ;
}

int main()
{
    scanf("%d%d",&n,&q) ;

    int root = sqrt(q) ;

    for(int i = 0 ; i < n - 1 ; i++){
          int u , v;
          scanf("%d%d",&u,&v) ;
          u-- , v-- ;
          tree[u].push_back(v);
          tree[v].push_back(u);
    }

    dp() ;

    vector < int > src ;
    src.push_back(0) ;

    vector < int > dist(n + 1, 1 << 30);

    for(int i = 0 ; i < q ; i++){

          if(i % root == 0){

               vector < int > t = bfs(src) ;

               for(int j = 0 ; j < n ; j++)
                  dist[j] = min(dist[j] , t[j]) ;

               src.clear() ;
          }


          int t , u ;
          scanf("%d%d",&t,&u);
          u-- ;

          if(t == 2){
              int mn = dist[u] ;
              for(auto v : src)
                   mn = min(mn , calc(u , v));

              printf("%d\n",mn) ;
          }

          else
              src.push_back(u) ;
    }


    return 0;
}
