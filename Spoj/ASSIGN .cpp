#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int n ;
vector < int > ve;
ll memo[20][1 << 20];

ll solve(int i , int mask){

   if(i == n) return 1 ;

   ll &ret = memo[i][mask];
   if(ret != -1) return ret ;

   ret = 0 ;
   for(int j = 0 ; j < n ; j++){
         if(mask & (1 << j)) continue ;
         if(ve[i] & (1 << j)){
               ret += solve(i + 1 , mask | (1 << j));
         }
   }

   return ret ;
}

int main() {

    int t ; scanf("%d",&t);

    while(t--){
          ve.clear() ;

          scanf("%d",&n);
          for(int i = 0 ; i < n ; i++){
               int mask = 0 ;
               for(int j = 0 ; j < n ; j++){
                    int x ; scanf("%d",&x);
                    if(x) mask = mask | (1 << j);
               }
               ve.push_back(mask);
          }

          memset(memo , -1 , sizeof memo);

          printf("%lld\n",solve(0 , 0)) ;
    }



    return 0;
}
