/*
	Idea :
		- for each mask we iterate over all possible mask's of the flipping mask
		- and if there's a sauce with that submask we try to take it
		- Sol : https://github.com/magdy-hasan/competitive-programming/blob/master/Other/ZOJ%20Get%20Sauce.cpp
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 16 ;
int n , m ;
typedef bitset < N > mask ;
int memo[(1 << 16) + 1] , exist[(1 << 16) + 1];


int solve(mask msk){

    int t = msk.to_ulong() ;

    if(t == (1 << n) - 1) return 0 ;

    int &ret = memo[t];
    if(ret != -1) return ret ;

    msk.flip() ;
    int cmask = msk.to_ulong() ;
    msk.flip() ;

    ret = 0 ;
    for(int smask = cmask ; smask ; smask = (smask - 1) & cmask){
          if(exist[smask]){
              mask tmask = smask ;
              ret = max(ret , 1 + solve(tmask | msk));
          }
    }

    return ret ;
}


int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    while(cin >> n >> m) {

         memset(memo , -1 , sizeof memo);
         memset(exist , 0 , sizeof exist);

         for(int i = 0 ; i < m ; i++){
              int k ; cin >> k ;
              mask msk ;
              for(int j = 0 ; j < k ; j++){
                  int x ; cin >> x ;
                  x-- ;
                  msk[x] = 1;
              }
              exist[msk.to_ulong()] = 1 ;
         }

         cout << solve(0) << endl ;
    }



    return 0;
}
