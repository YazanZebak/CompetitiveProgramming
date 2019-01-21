#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int n , k ;
vector < int > ve ;
ll solve(){

   ll mod[k + 1] ;
   memset(mod , 0 , sizeof mod) ;


   int sum = 0 ;
   for(int i = 0 ; i < n ; i++){
         sum += ve[i] ;
         mod[sum % k] ++ ;
   }

   ll res =0  ;
   for(int i = 0 ; i < k ; i++){
         if(mod[i] > 1)
              res += (mod[i] * (mod[i] - 1))/2 ;
   }

   res += mod[0];
   return res;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t;
    int C = 1 ;

    while(t--){
          ve.clear() ;
          int a , b , c ;
          cin >> a >> b >> c >> k >> n ;

          ve.push_back(a) ;
          for(int i = 1 ; i < n ; i++){
                int x = ve[i - 1] * b + c ;
                x %= k ;
                x ++ ;
                ve.push_back(x) ;
          }

          cout << "Case " << C++ << ": " <<  solve() << endl ;
    }


    return 0;
}
