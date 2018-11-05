#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll n , m , x , y ;

bool check(ll mid){
    return m + (n - mid) * y >= mid * x ;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> x >> y ;

    ll low = 0 , high = n , res = 0 ;
    while(low <= high){
          ll mid = (low + high)/2 ;
          if(check(mid))
              res = mid , low = mid + 1 ;
          else
              high = mid - 1;
    }

    cout << res << endl ;

    return 0;
}
