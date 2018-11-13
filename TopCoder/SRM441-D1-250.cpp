#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

bool vis[55];
vector < vector < int > > G(55) ;
void dfs(int node){
     vis[node] = 1 ;
     for(auto child : G[node])
           if(!vis[child]) dfs(child) ;
}

class PerfectPermutation{

public :

     int reorder(vector < int > P){

         memset(vis , 0 , sizeof vis) ;

         vector < int > ve = P ;

         for(int i = 0 ; i < P.size() ; i++){
               if(vis[ve[i]]) continue ;
               int temp = ve[i] ;
               while(!vis[temp]){
                     G[temp].push_back(ve[temp]) ;
                     G[ve[temp]].push_back(temp) ;
                     vis[temp] = 1;
                     temp = ve[temp] ;
               }
         }

         memset(vis , 0 , sizeof vis) ;

         int res = 0 ;
         for(int i = 0 ; i < P.size() ; i++)
              if(!vis[i])
                  res ++ , dfs(i) ;

         if(res == 1) res = 0 ;
         return res ;
     }
};

