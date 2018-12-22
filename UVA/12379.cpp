#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < vector < int > > G(10005) ;
bool vis[10005];
int dist[10005] ;
void dfs(int node){

     vis[node] = 1 ;

     for(auto child : G[node]){
          if(vis[child]) continue ;
          dist[child] = dist[node] + 1 ;
          dfs(child);
     }
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t;
    while(t--){

          int n ; cin >> n ;

          for(int i = 1 ; i <= n ; i++){
               int x ; cin >> x ;
               G[i].clear();
               for(int j = 0 ; j < x ; j++){
                     int u ; cin >> u ;
                     G[i].push_back(u);
               }
          }


          memset(dist , 0 , sizeof dist);
          memset(vis , 0 , sizeof vis);

          dfs(1);

          int root = (int)(max_element(dist + 1,  dist + n + 1) - dist) ;

          memset(dist , 0 , sizeof dist);
          memset(vis , 0 , sizeof vis);

          dfs(root) ;

          int mx = *max_element(dist + 1 , dist + n + 1) ;

          cout << mx + 2 * ((n - 1) - mx) << endl ;
    }

    return 0;
}
