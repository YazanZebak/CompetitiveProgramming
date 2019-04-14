/*
   Idea : 
   		- Suppose we are given a path with m edges for each pair of vertices (i,j) such that the product of the edges is maximum.
   		- Then to find the optimal path between i,j using m+1 edges can be done by trying all k=1,2,3,…,N and choose k
   		- such that the path i-k-j (where i-k has m edges, k-j is a direct edge) is optimal.
   		- That means, we take G[i][j][m+1] = max(G[i][k][m] * G[k][j][1]) for k = 1,2,...,N.
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const double eps = 1e-8;

double G[30][30][30];
int path[30][30][30];

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ;

    while(cin >> n){

         memset(G , 0 , sizeof G);

         for(int i = 1 ; i <= n ; i++){
             for(int j = 1 ; j <= n ; j++){
                   if(i == j) G[i][j][0] = 1 ;
                   else cin >> G[i][j][0] ;
                   path[i][j][0] = i ;
             }
         }

         vector < int > res ;
         bool ok = 1 ;

         for(int t = 1 ; t < n && ok ; t++){

               for(int k = 1 ; k <= n ; k++)
                 for(int i = 1 ; i <= n ; i++)
                    for(int j = 1 ; j <= n ; j++)
                        if(G[i][k][t - 1] * G[k][j][0] > G[i][j][t])
                              G[i][j][t] = G[i][k][t - 1] * G[k][j][0] , path[i][j][t] = k ;

               for(int i = 1 ; i <= n && ok ; i++){
                    if(G[i][i][t] > 1.01 - eps){
                          res.push_back(i);
                          int p = path[i][i][t] ;
                          for(int j = t - 1 ; j >= 0 ; j--){
                               res.push_back(p);
                               p = path[i][p][j];
                          }
                          res.push_back(i);
                          reverse(res.begin() , res.end());
                          cout << res[0] ;
                          for(int i = 1 ; i < res.size() ; i++)
                              cout << " " << res[i] ;
                          cout << endl ;
                          ok = 0 ;
                    }
               }

         }
         if(ok)
              cout << "no arbitrage sequence exists" << endl ;


    }



    return 0;
}
