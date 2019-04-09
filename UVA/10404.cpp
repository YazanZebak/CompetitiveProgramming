#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int  m ;
vector < int > ve ;
int memo[1000005][2];

int solve(int n , bool turn){

    if(n == 0){
          return (turn ? 1 : 2)  ;
    }

    int &ret = memo[n][turn];
    if(ret != -1) return ret ;

    ret = (turn ? -3 : 3);
    for(int i = m - 1 ; i >= 0 ; i--){
          if(ve[i] <= n){
               if(!turn) ret = min(ret , solve(n - ve[i] , !turn));
               else ret = max(ret , solve(n - ve[i] , !turn));
          }
    }
    if(ret == -3) ret = 1 ;
    if(ret == 3) ret = 2 ;

    return ret ;
}

int main()
{

    int n ;

    while(scanf("%d%d",&n,&m) != EOF){

        ve.clear() ;

         for(int i = 0 ; i < m ; i++){
                 int x ; scanf("%d",&x);
                 ve.push_back(x);
         }

         sort(ve.begin() , ve.end());

         memset(memo , -1 , sizeof memo);

         int t = solve(n , 0) ;

         puts( (t == 1 ? "Stan wins" : "Ollie wins") ) ;
    }
}
