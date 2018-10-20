#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main() {

    int t ; scanf("%d",&t);
    int c = 1;
    while(t--) {
        ll n , s1 , v1 , s2 , v2 ;
        scanf("%lld%lld%lld%lld%lld",&n,&s1,&v1,&s2,&v2);
        printf("Case #%d: ",c++);
        ll s = s1 * s2 , v = max(s2 * v1 , s1 * v2);
        ll res = n / s * v ;
        n %= s ;
        if(s1 < s2) swap(s1 , s2) , swap(v1 , v2) ;
        ll best = 0 ;
        for(ll i = 0 ; i * s1 <= n ; i++){
             best = max(best , (n - s1 * i)/s2 * v2 + i * v1) ;
        }
        res += best ;
        printf("%lld\n",res) ;
    }

    return 0;
}
