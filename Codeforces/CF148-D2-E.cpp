#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , m , sz[105];
ll dp[105][10005];
ll pre_sum[104][105];
ll memo[105][10005];

void f1(){

   for(int i = 1 ; i <= n ; i++ )
      for(int j = 1 ; j <= sz[i] ; j++)
          for(int k = 0 ; k <= j ; k++)
               dp[i][j] = max(dp[i][j] , pre_sum[i][k] +  (pre_sum[i][sz[i]] - pre_sum[i][sz[i] - j + k]) );
}

ll f2(int i , int rem)
{
     if(i > n) return rem == 0 ? 0 : - 1>>30 ;

     ll &ret = memo[i][rem];
     if(ret != -1) return ret ;

     for(int j = 0 ; j <= min(sz[i] , rem) ; j++)
            ret = max(ret , f2(i + 1 , rem - j) + dp[i][j] ) ;

     return ret ;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m  ;

    for(int i = 1 ; i <= n ; i++){
        cin >> sz[i];
        for(int j = 1 ; j <= sz[i] ; j++){
            int x ;
            cin >> x ;
            pre_sum[i][j] = x + pre_sum[i][j - 1];
        }

    }
    f1() ;
    memset(memo , -1 , sizeof(memo));
    cout << f2(1 , m) << endl ;

    return 0;
}
