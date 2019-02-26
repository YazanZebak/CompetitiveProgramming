#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const ll mod = 1e9 + 7 ;
typedef vector < ll > row  ;
typedef vector < row >  matrix ;


matrix zero(int n , int m) {
    return matrix(n , row(m , 0));
}

matrix identity(int n) {
    matrix ret = matrix(n , row(n , 0));
    for(int i = 0 ; i < n ; i++) ret[i][i] = 1 ;
    return ret ;
}

matrix multiply(const matrix &a , const matrix &b) {

    matrix ret = zero(a.size() , b[0].size()) ;

    for(int i = 0 ; i < a.size() ; i++)
        for(int k = 0 ; k < a[0].size() ; k++)
            for(int j = 0 ; j < b[0].size() && a[i][k] ; j++){
                ret[i][j] += (a[i][k] * b[k][j]) % mod ;
                ret[i][j] %= mod ;
            }

    return ret ;
}

matrix power(const matrix &A , ll k) {
    if(k == 0)
        return identity(A.size());

    if(k & 1)
        return multiply( A , power(A , k - 1) ) ;

    return power( multiply(A , A) , k / 2) ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ; cin >> n ;

    ll k ; cin >> k ;

    vector < ll > ve;

    for(int i = 0 ; i < n ; i++){
         ll x ; cin >> x;
         ve.push_back(x) ;
    }


    matrix res = zero(n , n) ;

    for(int i = 0 ; i < n ; i++){
         for(int j = 0 ; j < n ; j++){
               res[i][j] = __builtin_popcountll(ve[i] ^ ve[j]) % 3 == 0 ;
         }
    }

    res = power(res , k - 1);
    ll ans = 0 ;

    for(int i = 0 ; i < n ; i++ ){
        for(int j = 0 ; j < n ; j++){
             ans += res[i][j] ;
             ans %= mod ;
        }
    }

    cout << ans << endl ;

    return 0;
}
