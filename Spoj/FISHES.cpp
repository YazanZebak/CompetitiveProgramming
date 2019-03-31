#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll grid[101][101];
ll dp[101][101];

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;
    int c = 1;

    while(t--){

         memset(dp , 0 , sizeof dp);
         memset(grid , 0 , sizeof grid);

         ll n , m , h , k , t ;
         cin >> n >> m >> h >> k >> t ;

         for(int i = 1 ; i <= n ; i++){
             for(int j = 1 ; j <= m ; j++){
                  cin >> grid[i][j] ;
             }
         }

         vector < ll > res(k + 1 , 0) ;

         for(int i = 0 ; i < t ; i++){
               ll x ; cin >> x ;
               for(int j = 1 ; j <= k ; j++){
                       ll y ; cin >> y ;
                       res[j] += (x * y);
               }
         }

         for(int i = 1 ; i <= n ; i++)
            for(int j = 1 ; j <= m ; j++)
                grid[i][j] = res[grid[i][j]] ;

         for(int i = 1 ; i <= n ; i++){
             for(int j = 1 ; j <= m ; j++){
                  dp[i][j] = dp[i][j - 1] + grid[i][j] ;
             }
         }

         ll ret = LONG_MIN , best = LONG_MIN ;
         for(int i = 1 ; i <= m ; i++){
            for(int j = i ; j <= m ; j++){
                ll mis = 0 ;
                for(int k1 = 1 ; k1 <= n ; k1++){
                     ll sum = dp[k1][j] - dp[k1][j - i];
                     mis = (mis < 0) ? sum : mis + sum ;
                     best = max(best , mis);
                }
                ret = max(ret , best);
            }
         }

         cout << "Case #" << c++ << ":" << endl ;
         cout << ret + h << endl ;
    }


    return 0;
}
