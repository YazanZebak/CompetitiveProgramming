/*
    Idea: https://codeforces.com/blog/entry/7287
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int mod = 1e9 + 7 ;
ll fact[1001] ;
ll two[1001];

inline ll inv(ll a, ll mod){
    return a > 1 ? mod - inv(mod % a, a) * mod / a : 1;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    fact[0] = 1 , two[0] = 1  ;
    for(ll i = 1 ; i <= 1000 ; i++){
         fact[i] = i * fact[i - 1] ;
         two[i] = 2 * two[i - 1] ;
         two[i] %= mod;
         fact[i] %= mod ;
    }

    int n , m ;

    cin >> n >> m ;

    string s(n + 1 , '0') ;
    for(int i = 0  ; i < m ; i++){
          int x ; cin >> x ;
          s[x] = '1' ;
    }

    ll res = 1 ;
    ll base = 1 ;

    for(int i = 1 ; i <= n ; ){
          if(s[i] == '1'){
               i++ ;
               continue ;
          }
          int c = 0 , j = i ;
          while(j <= n && s[j] == s[i]) j++ , c++ ;


          base *= fact[c];
          base %= mod ;

          if(i != 1 && j <= n){
                res *= two[c - 1] ;
                res %= mod ;
          }
          i = j ;
    }

    base = fact[n - m] * inv(base , mod);
    base %= mod ;

    res *= base ;
    res %= mod ;

    cout << res << endl ;

    return 0;
}
