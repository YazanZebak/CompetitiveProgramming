#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main()
{
    ll n , m ;
    while(cin >> n >> m){
         if(!n && !m) break ;
         double res = (m - n + 1.0) * 1.0 / (m + 1.0) ;
         if(n > m) res = 0.0 ;
         if(n == 0) res = 1.0 ;
         printf("%f\n",res) ;
    }
    return 0;
}
