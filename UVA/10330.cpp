#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
ll cap[300][300];

int bfs(int src , int sink , vector < int > &parent){

    fill(parent.begin() , parent.end() , -1) ;
    queue < pair < int , int > > Q ;
    Q.push({src , INT_MAX});
    parent[src] = -2 ;
    while(!Q.empty()){
          auto p = Q.front();
          Q.pop() ;
          ll u = p.first , flow = p.second ;
          for(int v = 0 ; v <= n ; v++){
                if(parent[v] != -1 || cap[u][v] <= 0) continue ;
                parent[v] = u  ;
                ll new_flow = min(flow , cap[u][v]);
                if(v == sink) return new_flow ;
                Q.push({v , new_flow});
          }
    }

    return 0 ;
}


ll maxFlow(int src , int sink){

    ll flow = 0 ;
    vector < int > parent(n + 1) ;
    ll new_flow ;

    while(new_flow = bfs(src , sink , parent)){
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


    while(cin >> n) {

         memset(cap , 0 , sizeof cap);

         for(int i = 1 ; i <= n ; i++){
               int v ; cin >> v ;
               cap[i][i + n] = v;
         }

         int m ; cin >> m ;

         for(int i = 0 ; i < m ; i++){
              int u , v , c ;
              cin >> u >> v >> c ;
              cap[u + n][v] = c ;
         }

         int s , t ;
         cin >> s >> t ;

         for(int i = 0 ; i < s ; i++){
                int v ; cin >> v ;
                cap[0][v] = INT_MAX ;
         }

         for(int i = 0 ; i < t ; i++){
               int v ; cin >> v ;
               cap[v + n][2 * n + 1] = INT_MAX ;
         }

         n = 2 * n + 1 ;

         cout << maxFlow(0 , n) << endl ;
    }

    return 0;
}
