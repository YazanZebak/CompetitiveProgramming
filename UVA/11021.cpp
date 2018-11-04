#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

double dp[1005];
int main(){

    ios::sync_with_stdio(false) ;

    int t ; cin >> t ;
    int c = 1;

    while(t--){
          int n , m , k ;
          cin >> n >> k >> m ;

          memset(dp , 0 , sizeof dp) ;

          vector < double > P ;
          for(int i = 0 ; i < n ; i++){
              double x ; cin >> x ;
              P.push_back(x) ;
          }

          dp[1] = P[0] ;
          for(int i = 2 ; i <= m ; i++)
            for(int j = 0 ; j < n ; j++)
                dp[i] += P[j] * pow(dp[i - 1] , j) ;


          cout << fixed << setprecision(7);

          cout << "Case #" << c++ << ": " << pow(dp[m] , k) << endl ;
    }

    return 0;
}
