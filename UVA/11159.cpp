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
    int t ;
    cin >> t ;
    int c = 1;
    while( t-- ) {

        memset(cap , 0 , sizeof cap);
        int n , m ;
        cin >> n ;

        vector < int > A ;

        for(int i = 1 ; i <= n ; i++) {
            int x ; cin >> x ;
            A.push_back(x);
            cap[0][i] = 1  ;
        }

        cin >> m ;
        vector < int > B ;

        for(int i = 1 ; i <= m ; i++) {
            int x ; cin >> x ;
            B.push_back(x);
            cap[i + n][n + m + 1] = 1  ;
        }

        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m  ; j++){
                  if(A[i - 1] == 0){
                      if(B[j - 1] == 0) cap[i][j + n] = 1 << 30 ;
                      continue ;
                  }
                  if(B[j - 1] % A[i - 1] == 0) cap[i][j + n] = 1 << 30 ;
            }
        }
        cout << "Case " << c++ << ": " ;
        cout << maxFlow(0 , n + m + 1) << endl ;
    }


    return 0;
}
