#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , m ;
int cap[302][302];

int bfs(int src , int sink , vector < int > &parent){

    fill(parent.begin() , parent.end() , -1) ;
    queue < pair < int , int > > Q ;
    Q.push({src , INT_MAX});
    parent[src] = -2 ;
    while(!Q.empty()){
          auto p = Q.front();
          Q.pop() ;
          int u = p.first , flow = p.second ;
          for(int v = 0 ; v <= n  ; v++){
                if(parent[v] != -1 || cap[u][v] <= 0) continue ;
                parent[v] = u  ;
                int new_flow = min(flow , cap[u][v]);
                if(v == sink) return new_flow ;
                Q.push({v , new_flow});
          }
    }

    return 0 ;
}


int maxFlow(int src , int sink){

    int flow = 0 ;
    vector < int > parent(n + 1) ;
    int new_flow ;

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


    double s , v ;
    while(cin >> n >> m >> s >> v) {

         memset(cap , 0 , sizeof cap);

         vector < pair < double , double > > ve ;

         for(int i = 0 ; i < n ; i++){
               double x , y ;
               cin >> x >> y ;
               ve.push_back({x , y});
               cap[0][i + 1] = 1 ;
         }

         for(int i = 0 ; i < m ; i++){
              double x , y ;
              cin >> x >> y ;
              cap[i + 1 + n][n + m + 1] = 1 ;
              for(int j = 0 ; j < ve.size() ; j++){
                    double d = (x - ve[j].first) * (x - ve[j].first) + (y - ve[j].second) * (y - ve[j].second);
                    if(d > s * s * v * v) continue ;
                    cap[j + 1][i + 1 + n] = INT_MAX ;
              }
         }

         int res = n ;
         n = n + m + 1 ;
         cout <<  res - maxFlow(0 , n) << endl ;
    }

    return 0;
}
