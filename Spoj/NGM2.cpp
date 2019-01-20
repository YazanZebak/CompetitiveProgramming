#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll n , k ;
ll arr[20] ;
ll inc_exe(int idx = 0 , ll d = 1 , int sign = -1){
    if(idx == k){
        if(d == 1) return 0 ;
        return sign * n/d ;
    }
    return inc_exe(idx + 1 , d , sign) + inc_exe(idx + 1 , (d * arr[idx])/__gcd(d , arr[idx]) , sign * -1);
}

int main(){

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n >> k ;
    bool one = 0 ;
    for(int i = 0 ; i < k ; i++) cin >> arr[i] , one |= (arr[i] == 1) ;
    if(one) return cout << 0 << endl , 0 ;
    cout << n - inc_exe() << endl ;

    return 0;
}
