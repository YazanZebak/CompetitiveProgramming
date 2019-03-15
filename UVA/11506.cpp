#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int cap[202][202];
vector < int > parent ;

int bfs(int src , int sink){
    parent.clear() ;
    parent.resize(2 * sink + 1 , -1);

    queue < pair < int , int > > Q ;
    parent[src] = -2 ;
    Q.push({src , INT_MAX});
    while(!Q.empty()){
          auto p = Q.front() ;
          Q.pop() ;
          int u =p.first , flow = p.second ;
          for(int v = 1 ; v <= 2 * sink ; v++){
                if(parent[v] != -1 || cap[u][v] <= 0) continue ;
                int new_flow = min(flow , cap[u][v]);
                parent[v] = u ;
                if(v == sink) return new_flow ;
                Q.push({v , new_flow});
          }
    }
    return 0 ;
}
ll minCut(int src , int sink){

    ll flow = 0 , new_flow ;
    while(new_flow = bfs(src , sink)){
          flow += new_flow ;
          int cur = sink ;
          while(cur != src){
              int prev = parent[cur];
              cap[prev][cur] -= new_flow ;
              cap[cur][prev] += new_flow ;
              cur = prev ;
          }
    }

    return flow ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n , m ;

    while(cin >> n >> m){

          if(max(n , m) == 0) break ;

          memset(cap , 0 , sizeof cap);

          for(int i = 2 ; i <= n - 1  ; i++){
                  int u , c ;
                  cin >> u >> c ;
                  cap[u][u + n] = c ;
          }

          for(int i = 0 ; i < m ; i++){
                int u , v , c ;
                cin >> u >> v >> c ;

                if(u == 1)
                     cap[1][v] = c ;
                else if(v == n)
                      cap[u + n][v] = c ;
                else{
                     cap[u + n][v] = c;
                     cap[v + n][u] = c ;
                }
          }

          cout << minCut(1 , n) << endl ;
    }


    return 0;
}
