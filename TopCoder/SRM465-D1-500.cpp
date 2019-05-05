#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int cap[152][152];
vector < int > parent ;

int bfs(int src , int sink){
    parent = vector < int > (150 , 0);
    fill(parent.begin() , parent.end() , -1) ;
    parent[src] = -2 ;
    queue < pair < int , int > > Q ;
    Q.push({src , INT_MAX});

    while(!Q.empty()){
         auto p = Q.front() ;
         Q.pop() ;
         int u = p.first , flow = p.second ;
         for(int v = 0 ; v <= sink ; v++){
              if(parent[v] != -1 || cap[u][v] <= 0) continue ;
              parent[v] = u ;
              int new_flow = min(flow , cap[u][v]) ;
              if(v == sink) return new_flow ;
              Q.push({v , new_flow});
         }
    }

    return 0 ;
}

int maxFlow(int src , int sink){

    int flow = 0 ;
    int new_flow ;

    while(new_flow = bfs(src , sink)){
         flow += new_flow ;
         int cur = sink ;
         while(cur != src){
              int prev = parent[cur] ;
              cap[prev][cur] -= new_flow ;
              cap[cur][prev] += new_flow ;
              cur = prev ;
         }
    }

    return flow ;
}

class GreenWarfare{

public :

    int minimumEnergyCost(vector <int> canonX, vector <int> canonY, vector <int> baseX, vector <int> baseY, vector <int> plantX, vector <int> plantY, int energy){

        int n = canonX.size()  , m = baseX.size() , k = plantX.size() ;

        for(int i = 0 ; i < k ; i++){
            int mn = INT_MAX ;
            for(int j = 0 ; j < n ; j++){
                 int x = canonX[j] - plantX[i];
                 int y = canonY[j] - plantY[i];
                 int d = x * x + y * y  ;
                 mn = min(mn , d);
            }
            cap[0][i + 1] = mn  ;
        }

        for(int i = 0 ; i < m ; i++){
             int mn = INT_MAX ;
             for(int j = 0 ; j < n ; j++){
                  int x = canonX[j] - baseX[i];
                  int y = canonY[j] - baseY[i];
                  int d = x * x + y * y ;
                  mn = min(mn , d);
             }
             cap[i + 1 + k][m + k + 1] = mn ;
        }

        int src = 0 , sink = m + k + 1 ;

        for(int i = 0 ; i < m ; i++){
             for(int j = 0 ; j < k ; j++){
                   int x = baseX[i] - plantX[j];
                   int y = baseY[i] - plantY[j];
                   int d = x * x + y * y ;
                   if(d <= energy * energy) cap[j + 1][i + k + 1] = (1 << 30);
             }
        }

        return maxFlow(src , sink) ;
    }

};
