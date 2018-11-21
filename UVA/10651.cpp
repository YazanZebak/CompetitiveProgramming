#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

bool getbit(int num , int idx) {
    return ( num & (1 << idx) ) ;
}
int setbit(int num , int idx , int value) {
    return (value) ? ( num | (1 << idx) ): (num & ~(1 << idx) );
}

const int n = 12 ;
int memo[(1 << n) + 1];


int solve(int mask) {

    int &ret = memo[mask] ;
    if(ret != -1) return ret ;

    ret = __builtin_popcount(mask);


    for(int i = 0 ; i < n - 2 ; i++) {

        if(getbit(mask , i) && getbit(mask , i + 1) && !getbit(mask , i + 2)) {
            int tmask = mask ;
            tmask = setbit(tmask , i , 0);
            tmask = setbit(tmask , i + 1 , 0);
            tmask = setbit(tmask , i + 2 , 1);
            ret = min(ret , solve(tmask));
        }
        if(!getbit(mask , i) && getbit(mask , i + 1) && getbit(mask , i + 2)) {
            int tmask = mask ;
            tmask = setbit(tmask , i , 1);
            tmask = setbit(tmask , i + 1 , 0);
            tmask = setbit(tmask , i + 2, 0);
            ret = min(ret , solve(tmask));
        }
    }

    return ret ;
}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    int t ;
    cin >> t;

    while(t--) {
        string s;
        cin >> s;

        memset(memo , -1 , sizeof memo);
        int mask = 0 ;

        for(int i = 0 ; i < n ; i++) {
            if(s[i] == 'o') mask = setbit(mask , i , 1) ;
            else mask = setbit(mask , i , 0) ;
        }

        cout << solve(mask) << endl ;
    }



    return 0;
}
