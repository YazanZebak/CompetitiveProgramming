#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
const int N = 400 ;

bool G[N][N] , G2[N][N] , vis[N] ;
int dp[N];
vector < vector < int > > adj(N) ;
vector < int > topsort ;

void dfs(int u){

    vis[u] = 1 ;

    for(auto v : adj[u])
        if(!vis[v]) dfs(v);

    topsort.push_back(u);
}

class MarbleCollectionGame {

public:

    int get_val(char c){
        if(c <= '9' && c >= '0') return c - '0' ;
        return 0 ;
    }

    int collectMarble(vector < string > board){

        int n = board.size() , m = board[0].size();
        memset(G , 0 , sizeof G) ;

        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                int x = i * m + j , y ;
                if(board[i][j] == '#') continue ;

                if(i + 1 < n && board[i + 1][j] != '#')
                    y = (i + 1) * m + j , G[x][y] = 1 ;

                if(j + 1 < m && board[i][j + 1] != '#')
                    y = i * m + j + 1 , G[x][y] = 1 ;

                if(board[i][j] == 'L' && j - 1 >= 0 && board[i][j - 1] != '#')
                    y = i * m + j - 1 , G[x][y] = 1 ;

                if(board[i][j] == 'U' && i - 1 >= 0 && board[i - 1][j] != '#')
                    y = (i - 1) * m + j , G[x][y] = 1;
            }
        }

        int sz = n * m  ;

        for(int i = 0 ; i < sz ; i++){
            G[i][i] = 1 ;
            for(int j = 0 ; j < sz ; j++)
                G2[i][j] = G[i][j] ;
        }

        for(int k = 0 ; k < sz ; k++)
          for(int i = 0 ; i < sz ; i++)
           for(int j = 0 ; j < sz ; j++)
               G[i][j] |= (G[i][k] & G[k][j]) ;


        vector < int > sum(sz) , comp(sz , -1) ;
        int cnt = 0 ;

        for(int i = 0 ; i < sz ; i++){

              if(comp[i] != -1) continue ;

              comp[i] = cnt ++ ;

              for(int j = 0 ; j < sz ; j++)
                  if(G[i][j] && G[j][i]) comp[j] = comp[i]  ;
        }

        vector < vector < int > > comps(N);

        for(int i = 0 ; i < sz ; i++){
             comps[comp[i]].push_back(i);
        }

        for(int i = 0 ; i < cnt ; i++){
             for(auto u : comps[i]) sum[i] += get_val(board[u / m][u % m]);
        }

        for(int i = 0 ; i < sz ; i++){
              for(int j = 0 ; j < sz ; j++){
                  if(G[i][j])
                     adj[comp[i]].push_back(comp[j]);
              }
        }

        dfs(0) ;

        for(auto u : topsort){
            int best = 0  ;
            for(auto v : adj[u])
                  best = max(best , dp[v]) ;
            dp[u] = best + sum[u];
        }

        return dp[0] ;
    }


};
