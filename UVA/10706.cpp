#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll dp[100100];
string toStr(ll n) {
    string st ;
    while(n) {
        int c = n % 10 ;
        st.push_back(char('0' + c));
        n /= 10 ;
    }
    reverse(st.begin() , st.end());
    return st ;
}

int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    for(int i = 1 ; i <= 100000 ; i++) {
        dp[i] = dp[i - 1] + 1 + floor(log10(i)) ;
    }
    int t ;  cin >> t ;

    while(t--) {

        ll pos ; cin >> pos ;
        bool ok = 1;

        for(ll i = 1 ; ok ; i++) {
            if(pos > dp[i]) pos -= dp[i] ;
            else {
                ok = 0 ;
                for(ll j = 1; j <= i ; j++) {
                    ll res = 1 + floor(log10(j)) ;
                    if(pos > res) pos -= res;
                    else {
                        string st = toStr(j) ;
                        for(int k = 0 ; pos ; k++ , pos--) {
                            if(pos == 1) cout << st[k] << endl;
                        }
                        break ;
                    }
                }
            }
        }
    }

    return 0;
}
