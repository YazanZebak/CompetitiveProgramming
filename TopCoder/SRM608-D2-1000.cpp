#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

bool G[52][52] ;

class BigOEasy{

public :
    string isBounded(vector < string > graph){

        int n = (int)graph.size() ;

        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                  if(graph[i][j] == 'Y') G[i][j] = 1 ;
                  else G[i][j] = 0 ;
            }
        }

        for(int k = 0 ; k < n ; k++)
           for(int i = 0 ; i < n ; i++)
              for(int j = 0 ; j < n ; j++)
                  G[i][j] |= (G[i][k] & G[k][j]);

        vector < int > comp(n , -1);
        vector < vector < int > > comps(n);

        int cnt = 0 ;

        for(int i = 0 ; i < n ; i++){
             if(comp[i] != -1) continue ;
             comp[i] = cnt++;
             for(int j = 0 ; j < n ; j++)
                 if(G[i][j] && G[j][i]) comp[j] = comp[i];
        }

        for(int i = 0 ; i < n ; i++)
             comps[comp[i]].push_back(i);

        bool ok = 0 ;

        for(int i = 0 ; i < cnt ; i++){

              if(comps[i].size() < 3) continue ;


              for(auto u : comps[i]){
                    int t = 0 ;
                    for(int j = 0 ; j < graph[u].size() ; j++) if(graph[u][j] == 'Y' && comp[j] == comp[u] && j != u) t ++ ;
                    if(t >= 2) ok = 1 ;
              }

        }

        return (ok ? "Unbounded" : "Bounded");
    }

};
