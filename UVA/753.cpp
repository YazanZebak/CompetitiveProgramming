/*
    Idea:
      - Link the devices to the sink 
      - Link the receptacles to the src 
      - Link between the adapters in inf flow 
      - run the max flow algorithm and the answer will be (#devices - maxFlow)
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , m , k ;
int cap[500][500]  ;
map < string , int > name ;

int bfs(int src , int sink , vector < int > &parent){

    fill(parent.begin() , parent.end() , -1);
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
                int new_flow = min(cap[u][v] , flow) ;
                if(v == sink) return new_flow ;
                Q.push({v , new_flow});
          }
    }

    return 0 ;
}

int maxFlow(int src , int sink){

    vector < int > parent(sink + 1);
    int flow = 0 ;
    int new_flow ;

    while(new_flow = bfs(src , sink , parent)){
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

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;
    int c = 0 ;

    while(t--){

        cin >> n ;

        if(c) cout << endl ;

        c = 1 ;

        memset(cap , 0 , sizeof cap);
        name.clear() ;

        for(int i = 1 ; i <= n ; i++){
              string s ; cin >> s ;
              name[s] = i ;
        }

        cin >> m ;
        int cnt = n + 1;

        for(int i = 1 ; i <= m ; i++){
              string s , u ;
              cin >> s >> u ;
              if(!name[u]) name[u] = cnt++ ;
              cap[0][name[u]]++;
        }

        cin >> k ;

        for(int i = 0 ; i < k ; i++){
              string s1 , s2 ;
              cin >> s1 >> s2;
              if(!name[s1]) name[s1] = cnt ++ ;
              if(!name[s2]) name[s2] = cnt ++ ;

              int u = name[s1] , v = name[s2] ;
              cap[u][v] = INT_MAX ;
        }

        for(int i = 1 ; i <= n ; i++) cap[i][cnt] = 1 ;

        cout << m - maxFlow(0 , cnt) << endl ;

    }
    return 0;
}
