#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n ;
    cin >> n ;

    vector < vector < int > > grid(n) ;

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            int x ;
            cin >> x;
            grid[i].push_back(x) ;
        }
    }
    int res = INT_MIN ;

    for(int i = 0 ; i < n ; i++) {

        int j = 0 ;
        int i1 = i + 1 , j1 = j + 1 ;
        i1 %= n , j1 %= n ;
        int sum = 0 ;
        sum += grid[i][j] ;

        while(i1 != i && j1 != j) {
            sum += grid[i1][j1] ;
            i1 ++ , j1 ++ ;
            i1 %= n , j1 %= n ;
        }

        res = max(res , sum);
    }

    cout << res << endl ;

    return 0;
}
