#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main(){

    ios::sync_with_stdio(false);

    int n , m  ;
    cin >> n >> m ;

    int fr , fc , sr , sc ;
    cin >> fr >> fc >> sr >> sc ;

    int res = 0 ;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
              int d1 = abs(i - fr) + abs(j - fc) ;
              int d2 = abs(i - sr) + abs(j - sc) ;
              if(d1 == d2) res++ ;
        }
    }

    cout << res << endl ;

    return 0;
}
