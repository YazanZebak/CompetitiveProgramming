#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
string s ;
int memo[(1 << 20) + 1][2] ;


bool check(int mask , int i) {
    return (mask & (1 << i)) ;
}

int setbit(int num , int idx , int value) {
    return (value) ? ( num | (1 << idx) ): (num & ~(1 << idx) );
}

int solve(int mask , bool turn) {

    if(mask == 0) {
        if(turn == 1) return 1 ;
        else return 2 ;
    }

    int &ret = memo[mask][turn];
    if(ret != -1) return ret ;

    ret = (turn ? -3 : 3) ;
    for(int i = 0 ; i < n ; i++) {

        int c1 = ret ;
        if(i + 1 < n && check(mask , i) && !check(mask , i + 1)) {
            if(i + 1 == n - 1)
                c1 = solve((mask & ~(1 << i)) , !turn);
            else {
                mask = setbit(mask , i , 0) ;
                mask = setbit(mask , i + 1 , 1) ;
                c1 = solve(mask , !turn) ;
                mask = setbit(mask , i , 1) ;
                mask = setbit(mask , i + 1 , 0) ;
            }
        }

        if(i + 3 < n && check(mask , i) && check(mask , i + 1) && check(mask , i + 2) && !check(mask,  i + 3)) {
            if(i + 3 == n - 1)
                c1 = solve((mask & ~(1 << i)) , !turn);
            else {
                mask = setbit(mask , i , 0) ;
                mask = setbit(mask , i + 3 , 1) ;
                c1 = solve(mask , !turn) ;
                mask = setbit(mask , i , 1) ;
                mask = setbit(mask , i + 3 , 0) ;
            }
        }

        if(turn) ret = max(ret , c1);
        else ret = min(ret , c1) ;

    }

    if(ret == -3) ret = 1 ;
    if(ret == 3) ret = 2 ;

    return ret ;
}


class EllysCheckers {

public :
    string getWinner(string board) {

        s = board ;
        n = (int)s.size() ;
        memset(memo , -1 , sizeof memo);

        int mask = 0 ;

        for(int i = 0 ; i < n - 1 ; i++){
              if(s[i] != '.') mask |= (1 << i) ;
        }

        return (solve(mask , 0) == 1 ? "YES" : "NO") ;
    }
};
