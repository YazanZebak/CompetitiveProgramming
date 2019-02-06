#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < int > query[500];
int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n ; cin >> n ;
    int Q ; cin >> Q ;

    int root = sqrt(n) ;
    int cnt = (n + root - 1) / root ;

    vector < int > ve;

    for(int i = 0 ; i < n ; i++) {
        int x ; cin >> x;
        ve.push_back(x);
        query[i / root].push_back(x);
    }

    for(int i = 0 ; i < cnt ; i++)
        sort(query[i].begin() , query[i].end());

    while(Q--) {
        char c ;
        cin >> c ;
        int ans = 0 ;

        if(c == 'C') {

            int l , r,  x;
            cin >> l >> r >> x ;
            l-- , r-- ;

            for(int j = l ; j <= r ; j++) {
                if(j % root == 0 && j + root - 1 <= r) {
                    ans += upper_bound(query[j / root].begin() , query[j / root].end() , x) - query[j / root].begin();
                    j += root - 1;
                } else if(ve[j] <= x)
                    ans ++ ;
            }

            cout << ans << endl;
        } else {
            int l , x;
            cin >> l >> x;

            l-- ;
            ve[l] = x;
            int j = l / root ;
            query[j].clear() ;

            for(int i = j * root ; i < min(n , (j + 1) * root ); i++)
                query[j].push_back(ve[i]);

            sort(query[j].begin() , query[j].end());
        }
    }

    return 0;
}
