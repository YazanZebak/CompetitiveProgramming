#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , m ;
vector < ll > ve;
ll memo[11][31];

ll solve(int i , int last){

    if(i == m) return (last < n ? 1LL << 32 : 0);
    if(last == n) return 0 ;

    ll &ret = memo[i][last];
    if(ret != -1) return ret ;

    ll temp = 0 ;
    ret = 1LL << 32 ;
    for(int j = last , k = 1 ; j < n ; j++ , k ++){
         temp += (k * ve[j]) ;
         ret = min(ret , temp + solve(i + 1 , j + 1)) ;
    }

    return ret ;
}

vector < int > res(11 , 0) ;
void build(int i , int last){

    if(i == m) return ;
    if(last == n) return ;

    ll optimal = solve(i , last) ;
    ll temp = 0 , ret = 1LL << 32 ;

    for(int j = last , k = 1 ; j < n ; j ++ , k ++){
           temp += (k * ve[j]) ;
           ret = min(ret , temp + solve(i + 1 , j + 1)) ;
           if(ret == optimal){
               res[i] = k ;
               build(i + 1 , j + 1) ;
               break ;
           }
    }
}

int main(){

#ifdef ONLINE_JUDGE
    freopen("sms.in" , "r" , stdin) ;
    freopen("sms.out" , "w" , stdout) ;
#endif

    scanf("%d%d",&n,&m) ;

    for(int i = 0 ; i < n ; i++){
          int x ; scanf("%d",&x) ;
          ve.push_back(x);
    }

    memset(memo , -1 , sizeof memo) ;
    solve(0 , 0) ;

    build(0 , 0) ;

    printf("%d",res[0]) ;
    for(int i = 1 ; i < m ; i++)
         printf(" %d",res[i]) ;

}
