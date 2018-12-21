#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int lcm(int a , int b) {
    return a / __gcd(a , b) * b ;
}

int main() {

    ios::sync_with_stdio(false);

    int n ;
    while(cin >> n && n ) {

        int res = 0 ;
        vector < int > ve;

        for(int i = 1 ; i * i <= n ; i++) {
            if(n % i == 0) {
                ve.push_back(i);
                if(n / i != i) ve.push_back(n / i) ;
            }
        }

        for(int i = 0 ; i < ve.size() ; i++){
             for(int j = i ; j < ve.size() ; j++){
                  if(lcm(ve[i] , ve[j]) == n) res ++ ;
             }
        }

        cout << n << " " << res << endl ;
    }


    return 0;
}
