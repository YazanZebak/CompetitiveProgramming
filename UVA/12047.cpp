#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
const ll inf = 1LL << 60 ;

vector < ll > dijkstra(vector < vector < pair < int , int > > > &G , int src){

     priority_queue < pair < ll , ll > , vector < pair < ll , ll > > , greater < pair < ll , ll > > > Q ;
     vector < ll > dist(n + 1 , inf);

     Q.push({0 , src});
     dist[src] = 0 ;

     while(!Q.empty()){
           auto p = Q.top() ;
           Q.pop() ;
           int node = p.second ;
           ll weight = p.first ;

           if(weight > dist[node]) continue ;

           for(auto e : G[node]){
                 int child = e.first ;
                 int w = e.second ;
                 if(dist[child] > dist[node] + w){
                      dist[child] = dist[node] + w ;
                      Q.push({dist[child] , child}) ;
                 }
           }
     }

     return dist ;
}

int main()
{
    int t ; scanf("%d",&t);

    while(t--){
          int m , src , trg , p ;
          scanf("%d%d%d%d%d",&n,&m,&src,&trg,&p) ;

          vector < vector < pair < int , int > > > G1(n + 1) , G2(n + 1) ;
          vector < pair < int , pair < int , int > > > edges ;

          for(int i = 0 ; i < m ; i++){
                 int u , v , w ;
                 scanf("%d%d%d",&u,&v,&w) ;
                 G1[u].push_back({v , w}) ;
                 G2[v].push_back({u , w}) ;
                 edges.push_back({u , {v , w}}) ;
          }

          vector < ll > dist1 = dijkstra(G1 , src) ;
          vector < ll > dist2 = dijkstra(G2 , trg) ;

          int res = -1 ;

          for(auto i : edges){
                int u = i.first ;
                int v = i.second.first ;
                int w = i.second.second ;

                if(dist1[u] + w + dist2[v] <= p)
                       res = max(res , w) ;
          }

          printf("%d\n",res) ;
    }

    return 0;
}
