#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
const int N = 1e5 + 10 ;

vector < int > G[N] ;
ll sz[N] , res[N] , cnt[N] , col[N];
bool heavy[N] ;
ll maxx , sum ;

void dfs(int u , int p){
    sz[u] = 1;
    for(auto v : G[u]) if(v != p){
         dfs(v , u);
         sz[u] += sz[v] ;
    }
}

void add(int node , int parent , int val){


      cnt[ col[node] ] += val ;

      if(maxx < cnt[ col[node] ] )
          maxx = cnt[ col[node] ] , sum = col[node] ;
      else if(maxx == cnt[ col[node] ])
          sum += col[node] ;

     for(auto child : G[node]){
          if(child != parent && !heavy[child])
              add(child , node , val);
     }
}

void dfs(int node , int parent , bool keep){

     int mx = -1 , big = -1 ;
     for(auto child : G[node]){
            if(child == parent) continue ;
            if(sz[child] > mx){
                  mx = sz[child] ;
                  big = child  ;
            }
     }

     for(auto child : G[node]){
          if(child == parent) continue ;
          if(child == big) continue ;
          dfs(child , node , 0) ;
     }

     if(big != -1)
          dfs(big , node , 1) , heavy[big] = 1;

     add(node , parent , 1);

     res[node] = sum ;

     if(big != -1)
          heavy[big] = 0 ;
     if(keep == 0)
          add(node , parent , -1) , maxx = sum = 0 ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ; cin >> n ;

    for(int i = 1 ; i <= n ; i++) cin >> col[i] ;

    for(int i = 1; i < n ; i++){
          int u , v;
          cin >> u >> v ;
          G[u].push_back(v);
          G[v].push_back(u);
    }

    dfs(1 , -1);
    dfs(1 , -1 , 0);


    for(int i = 1;  i <= n ; i++)
         cout << res[i] <<  " " ;

    return 0;
}