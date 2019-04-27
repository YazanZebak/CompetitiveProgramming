#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int main()
{
    int t ; cin >> t;

    while(t--){
         int n ; cin >> n ;
         double res = 1 ;
         int m = (n - 2) / 2 ;

         int p = n - 2 ;

         for(int i = 1 , j = m + 1 ; i <= m ; i++ , j++){
               res *= (1.0 * j / i) ;
               while(res > 1 && p) res *= 0.5 , p-- ;
         }
         while(p) res *= 0.5 , p-- ;

         printf("%.4f\n",1.0 - res) ;
    }

    return 0;
}
