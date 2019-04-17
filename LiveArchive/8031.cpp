#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int inf = 1e9 + 10 ;

int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0)  ;

    int t ;
    cin >> t ;

    while(t--) {
        ll n , x , y , z ;
        cin >> x >> y >> z >> n ;

        if(n == 0){
              x-- , y-- , z-- ;
              ll res = (x ^ y ^ z) ;
              if(res) cout << "Alice" << endl ;
              else cout << "Bob" << endl ;
              continue ;
        }

        ll mn[3] = {inf , inf , inf} , mx[3] = {0 , 0 , 0} ;

        for(int i = 0 ; i < n ; i++) {
             for(int j = 0 ; j < 3 ; j++){
                  ll c ; cin >> c;
                  mn[j] = min(mn[j] , c) ;
                  mx[j] = max(mx[j] , c) ;
             }
        }

        int res = 0 ;
        for(int i = 0 ; i < 3 ; i++){
              res ^= (mn[i] - 1);
              int c = 0 ;
              if(i == 0) c = x - mx[i];
              if(i == 1) c = y - mx[i];
              if(i == 2) c = z - mx[i];
              res ^= c ;
        }

        if(res) cout << "Alice" << endl ;

        else cout << "Bob" << endl ;
    }

    return 0;
}
