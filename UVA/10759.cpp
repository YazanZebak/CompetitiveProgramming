#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , x ;
ll dp[25][151];

int main() {

    ios::sync_with_stdio(false) ;

    memset(dp , 0 , sizeof dp) ;

    for(int i = 1 ; i <= 24 ; i++) {
        for(int j = 1 ; j <= 150 ; j++) {
            if(i == 1 && j <= 6)
                dp[i][j] = 1;
            for(int k = 1 ; k <= 6 ; k++)
                if(j >= k)
                    dp[i][j] += dp[i - 1][j - k] ;
        }
    }

    for(int i = 1 ; i <= 24 ; i++)
        for(int j = 149 ; j >= 0 ; j--)
            dp[i][j] += dp[i][j + 1];

    while(cin >> n >> x && n) {

        ll sub = dp[n][x] ;
        ll tot = dp[n][0] ;

        ll g = __gcd(sub , tot) ;

        sub /= g , tot /= g ;
        if(sub == 0) {
            cout << 0 << endl ;
            continue ;
        }
        if(sub == 1 && tot == 1) {
            cout << 1 << endl ;
            continue ;
        }

        cout << sub << "/" << tot << endl ;
    }


    return 0;
}
