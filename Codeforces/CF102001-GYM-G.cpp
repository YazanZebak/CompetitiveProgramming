// editorial : https://github.com/jonathanirvings/icpc-jakarta-2018/blob/master/icpc18-analysis.pdf
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n, m ;
bool G[501][501];
bool T[501][501];
int degree[501];


bool check(int mid) {

    memset(degree, 0, sizeof degree);

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
            T[i][j] = G[i][j];

    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1 ; j <= n ; j++) {
            if(i == j)
                continue ;
            if(G[i][j])
                degree[i]++ ;
        }
    }


    while(true) {

        bool ok = 0 ;

        for(int i = 1 ; i <= n ; i++) {
            for(int j = 1 ; j <= n ; j++) {
                if(T[i][j])
                    continue ;

                if(degree[i] + degree[j] >= mid) {
                    T[i][j] = T[j][i] = 1 ;
                    degree[i]++ ;
                    degree[j]++ ;
                    ok = 1 ;
                }
            }
        }

        if(!ok)
            break ;
    }

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
            if(T[i][j] == 0)
                return false;

    return true ;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m ;

    for(int i = 1 ; i <= n ; i++)
        G[i][i] = 1;

    for(int i = 0 ; i < m ; i++) {
        int x, y ;
        cin >> x >> y;
        G[x][y] = G[y][x] = 1 ;
    }

    int low = 0, high = 4 * n, res = 0 ;
    while(low <= high) {
        int mid = (low + high)/2 ;
        if(check(mid))
            res = mid, low = mid + 1;
        else
            high = mid - 1 ;
    }

    cout << res << endl ;

    return 0;
}
