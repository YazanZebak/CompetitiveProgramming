#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


ll dp[5006][5006];
const ll inf = 1LL << 60 ;
int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n , k , x ;
    cin >> n >> k >> x ;

    vector < int > ve ;
    for(int i = 0 ; i < n ; i++) {
        int x ;
        cin >> x;
        ve.push_back(x);
    }
    for(int i = 0 ; i < n ; i++) dp[i][x] = -inf ;

    dp[n][x] = 0 ;

    for(int j = x - 1 ; j >= 0;  j--) {
        deque < pair < ll , ll > > Q ;
        for(int i = n - 1 ; i >= 0 ; i--) {
            ll val = dp[i + 1][j + 1];
            dp[i][j] = -inf ;
            while(!Q.empty() && val >= Q.back().second) Q.pop_back();
            Q.push_back(make_pair(i + 1 , val));

            if(Q.front().first - i > k) Q.pop_front() ;
            dp[i][j] = max(dp[i][j] , Q.front().second + ve[i]);
        }
    }

    ll res = -1 ;
    for(int i = 0 ; i < k ; i++)
        res = max(res , dp[i][0]);

    cout << res << endl;

    return 0;
}
