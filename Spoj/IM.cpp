/*
    Idea : https://www.quora.com/How-can-I-approach-the-problem-Intergalactic-Map-IM-on-SPOJ-using-Max-Flow
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < vector < pair < int , int > > > G;

void removeEdge(int u , int v , int w){
     for(auto &c : G[u]){
          if(c.first != v) continue;
          c.second -= w;
          return ;
     }
}

void addEdge(int u , int v , int w){
    for(auto &c : G[u]){
          if(c.first != v) continue ;
          c.second += w ;
          return ;
    }
    G[u].push_back({v , w});
}

int bfs(int src , int sink , vector < int > &parent)
{
	fill(parent.begin() , parent.end() , -1) ;
	parent[src] = -2 ;

	queue < pair < int , int > > Q ;
	Q.push({src , INT_MAX});

	while(!Q.empty()){
		 auto p = Q.front() ;
		 Q.pop() ;
		 int u = p.first , flow = p.second ;
		 for(auto v : G[u]){
		 	  if(parent[v.first] != -1 || v.second <= 0) continue ;
		 	  parent[v.first] = u ;
		 	  int new_flow = min(flow , v.second);
		 	  if(v.first == sink) return new_flow ;
		 	  Q.push({v.first , new_flow});
		 }
	}

	return 0 ;
}

int maxFlow(int src , int sink){

    int flow = 0 ;
    vector < int > parent(sink + 1) ;
    int new_flow = 0 ;

    while(new_flow = bfs(src , sink , parent)){
         flow += new_flow ;
         int cur = sink  ;
         while(cur != src){
               int prev = parent[cur];
               removeEdge(prev , cur , new_flow);
               addEdge(cur , prev , new_flow);
               cur = prev ;
         }
    }

    return flow ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){

         int n , m ;
         cin >> n >> m ;

         G.clear() ;
         G.resize(2 * n + 2);

         for(int i = 1 ; i <= n ; i++){
               if(i == 2) continue ;
               G[i].push_back({i + n , 1});
         }

         for(int i = 0 ; i < m ; i++){
                int u , v ;
                cin >> u >> v ;

                if(u > n || v > n) continue ;

                if(u == 2)
                    G[u].push_back({v , 1});
                else if(v == 2)
                    G[v].push_back({u , 1});
                else{
                     G[u + n].push_back({v , 1});
                     G[v + n].push_back({u , 1});
                }
         }

         G[3 + n].push_back({2 * n + 1 , 1});
         G[1 + n].push_back({2 * n + 1 , 1});

         if(maxFlow(2 , 2 * n + 1) == 2) cout << "YES" << endl ;
         else cout << "NO" << endl ;
    }
    return 0;
}
