// Link : http://zobayer.blogspot.com/2010/02/primitive-root.html

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < int > fact(int n) {

    vector < int > ret ;
    for(int i = 2 ; i * i <= n ; i++) {
        if(n % i == 0) {
            ret.push_back(i) ;
            while(n % i == 0)
                n /= i ;
        }
    }
    if(n != 1) ret.push_back(n);

    return ret;
}

ll bigMod(ll x , ll y , ll m){
    if (y == 0)
        return 1 % m;
    if (y % 2 == 0){
        ll temp = bigMod(x, y / 2, m);
        return (temp*temp) % m;
    }
    return (x%m * bigMod(x, y - 1, m)) % m;
}

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int n, t ;
    while( cin >> n >> t ) {

        if(!n && !t) break ;

        vector < int > prime = fact(n - 1);

        while(t--) {
            int a ; cin >> a;
            bool ok = 1;

            for(auto p : prime){
                if(bigMod(a , (n - 1) / p , n) == 1) ok = 0 ;
            }

            cout << (ok ? "YES" : "NO") << endl ;
        }
    }


}
