#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n ;
string s ;
vector < ll > ve ;
ll memo[101][101][101] ;

ll solve(int i , int j , int prefix){

   if(i > j)
       return 0;

   if(i == j)
        return ve[prefix] ;

   ll &ret = memo[i][j][prefix] ;

   if(ret != -1)
       return ret ;

   ret = ve[prefix] + solve(i + 1 , j , 1) ;

   for(int k = i + 1 ; k <= j ; k++){
          if(s[k] == s[i])
              ret = max(ret , solve(i + 1 , k - 1 , 1) + solve(k , j , prefix + 1)) ;
   }

   return ret ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n  ;
    cin >> s ;
    ve.push_back(0) ;

    for(int i = 0 ; i < n ; i++){
         int x ; cin >> x ;
         ve.push_back(x) ;
    }

    memset(memo , -1 , sizeof memo);

    cout << solve(0 , n - 1 , 1);


    return 0;
}
