#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int n ;
int memo[12][1 << 12] ;
ll fact[13];

int solve(int i , int mask){

    if(i == n)
          return 1;

    int &ret = memo[i][mask];
    if(ret != -1) return ret;

    ret = 0 ;
    for(int j = 0 ; j < n ; j++){
          if(i == j) continue ;
          if(mask & (1 << j)) continue ;
          ret += solve(i + 1 , mask | (1 << j));
    }

    return ret;
}

int main()
{
    ios::sync_with_stdio(false) ;

    fact[1] = 1;
    for(int i = 2 ; i <= 12 ; i++)
        fact[i] = (i * fact[i - 1]) ;

    int t ; cin >> t;

    while(t--){
          memset(memo , -1 , sizeof memo) ;
          cin >> n ;
          cout << solve(0 , 0) << "/" << fact[n] << endl ;
    }


    return 0;
}
