#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


bool cover[1 << 16];
ll memo[1 << 16] ;

ll solve(int mask) {

    if(mask == 0) return 0 ;

    ll &ret = memo[mask] ;
    if(ret != -1) return ret ;

    ret = 0 ;
    for(int i = mask ; i > 0 ; i = (i - 1) & mask)
       if(cover[i])
         ret = max(ret , 1 + solve(mask & ~i) ) ;

    return ret ;
}

int main() {

    ios::sync_with_stdio(false) ;

    int n , c = 1 ;

    while(cin >> n) {
        if(!n) break ;

        memset(cover , 0 , sizeof cover);
        memset(memo , -1 , sizeof memo);

        vector < vector < int > > G(n + 1) ;
        for(int i = 0 ; i < n ; i++) {
            int x ;
            cin >> x ;
            while(x--) {
                int j ;
                cin >> j ;
                G[i].push_back(j) ;
            }
        }

        for(int mask = 0 ; mask < (1 << n) ; mask ++ ) {
            int subMask = 0 ;
            for(int i = 0 ; i < n ; i++) if(mask & (1 << i)) {
                    subMask |= (1 << i) ;
                    for(auto j : G[i]) subMask |= (1 << j) ;
            }
            if(subMask == (1 << n) - 1) cover[mask] = 1 ;
        }

        cout << "Case " << c++ << ": " <<  solve( (1 << n) - 1) << endl ;
    }

    return 0;
}
