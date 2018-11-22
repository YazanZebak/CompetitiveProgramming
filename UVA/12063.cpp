#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

ll memo[64][64][101];
int n , k ;

ll solve(int i , int cnt0 , int cnt1 , int rem){

   if(i == n) return (rem == 0 && cnt0 == cnt1) ;

   ll &ret = memo[i][cnt0][rem] ;
   if(ret != -1) return ret ;

   if(i == n - 1){
         return ret = solve(i + 1 , cnt0 , cnt1 + 1 , (rem + (1LL << i)) % k );
   }

   ll c1 = solve(i + 1 , cnt0 + 1 , cnt1 , rem);
   ll c2 = solve(i + 1 , cnt0 , cnt1 + 1 , (rem + (1LL << i)) % k);

   return ret = c1 + c2 ;
}

int main()
{
    ios::sync_with_stdio(false);



    int t; cin >> t;
    int c = 1;
    while(t--){
             cin >> n >> k ;
             cout << "Case " << c++ << ": " ;
             if(n & 1){
                  cout << 0 << endl ;
                  continue ;
             }
             if(k == 0){
                  cout << 0 << endl ;
                  continue ;
             }
             memset(memo , -1 , sizeof memo);
             cout << solve(0 , 0 , 0 , 0) << endl ;
    }


    return 0;
}
