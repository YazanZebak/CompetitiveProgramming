#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
ll k ;
vector < int > ve ;

bool check(ll mid) {

    ll cnt = 0 , sum = 0 ;
    int l = 0 , r = 0 ;
    while(l < n) {
        while(r < n && sum + ve[r] <= mid) {
            sum += ve[r]  ;
            r++ ;
        }
        cnt += (r - l);
        sum -= ve[l] ;
        l++ ;
    }

    return cnt >= k ;
}

int main() {

    scanf("%d%lld",&n,&k);


    ll sum = 0 ;
    for(int i = 0 ; i < n ; i++) {
        int x ; scanf("%d",&x) ;
        ve.push_back(x) ;
        sum += x ;
    }

    ll low = 0 , high = sum  , res = sum ;
    while(low <= high) {
        ll mid = (low + high)/2 ;
        if(check(mid))
            res = mid , high = mid - 1 ;
        else
            low = mid + 1;
    }

    printf("%lld\n",res) ;

    return 0;
}
