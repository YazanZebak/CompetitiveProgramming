#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int cap[602][602];
vector < int > parent ;

int bfs(int src , int sink){

    parent.resize(sink + 1);
    fill(parent.begin() , parent.end() , -1);
    parent[src] = -2 ;
    queue < pair < int , int > > Q ;
    Q.push({src , INT_MAX});
    while(!Q.empty()){
          auto p = Q.front() ;
          Q.pop();
          int u = p.first , flow = p.second ;
          for(int i = 0 ; i <= sink ; i++){
              if(parent[i] != -1 || cap[u][i] <= 0) continue ;
              parent[i] = u ;
              int new_flow = min(flow , cap[u][i]);
              if(i == sink) return new_flow ;
              Q.push({i , new_flow});
          }
    }

    return 0 ;
}

int maxFlow(int src , int sink){

    int flow = 0 , new_flow ;
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

int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n , m ;
    while( cin >> n >> m ) {

        if(!n && !m) break ;

        memset(cap , 0 , sizeof cap);

        for(int i = 0 ; i < n ; i++) {
            int x ; cin >> x ;
            if(x == 0) cap[0][i + 1] = 1;
            else cap[i + 1][n + 1] = 1 ;
        }

        for(int i = 0 ; i < m ; i++) {
            int u , v ;
            cin >> u >> v ;
            cap[u][v] = cap[v][u] = 1;
        }


        cout << maxFlow(0 , n + 1) << endl ;
    }


    return 0;
}
