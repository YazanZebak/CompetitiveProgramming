#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


double dp[1 << 18];
double p[20][20];
int n ;

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;


    cin >> n ;

    for(int i  = 0 ; i < n ; i++)
        for(int j  = 0 ; j < n ; j++){
            cin >> p[i][j] ;
        }


    dp[(1 << n) - 1] = 1 ;
    for(int mask = (1 << n) - 1 ; mask >= 0 ; mask--){


           vector < int > tmask ;
           for(int i = 0 ; i < n ; i++) if(mask & (1 << i)) tmask.push_back(i);

           if(tmask.size() <= 1) continue ;
           int sz = tmask.size() ;
           double t = sz * (sz - 1) / 2.0;



           for(int i = 0 ; i < tmask.size() ; i++){
              for(int j = i + 1 ; j < tmask.size() ; j++){
                   int i1 = tmask[i] , i2 = tmask[j] ;
                   dp[mask & ~(1 << i2)] += (dp[mask] * p[i1][i2]) / t ;
                   dp[mask & ~(1 << i1)] += (dp[mask] * p[i2][i1]) / t  ;
              }
           }

    }


    cout << fixed << setprecision(6) ;
    for(int i = 0 ; i < n ; i++)
         cout << dp[1 << i]  << " " ;

    return 0;
}
