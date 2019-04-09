#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int n ;
string s ;
int memo[(1 << 15) + 1][2];

int solve(int mask , bool turn){

    int cnt = 0 , id = -1 ;
    for(int i = 0 ; i < n ; i++){
          if(!(mask & (1 << i))) id = i ;
          else cnt ++ ;
    }

    if(cnt == n - 1){
          return (s[id] == 'A' ? 1 : 2);
    }

    int &ret = memo[mask][turn];
    if(ret != -1) return ret ;

    ret = (turn ? -3 : 3);
    for(int i = 0 ; i < n ; i++){

          int tmask = 0 ;
          for(int j = i ; j < n ; j++){

                if(mask & (1 << j)) break ;

                tmask |= (1 << j);

                if(tmask | mask == (1 << n) - 1) break ;

                if(!turn) ret = min(ret , solve(mask | tmask , !turn));
                else ret = max(ret , solve(mask | tmask , !turn));
          }
    }

    if(ret == -3) ret = 1 ;
    if(ret == 3) ret = 2;

    return ret ;
}

class RowAndCoins{

public :
    string getWinner(string cells){

        s = cells ;
        n = s.size() ;        memset(memo , -1 , sizeof memo);

        return solve(0 , 0) == 1 ? "Alice" : "Bob" ;
    }
};
