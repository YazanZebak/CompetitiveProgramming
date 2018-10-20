#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


int main() {

    int t ; scanf("%d",&t) ;

    while(t--) {
        int n ; scanf("%d",&n) ;
        char in[n + 1] ; scanf("%s",in) ;
        string s = (string)in ;
        ll num ; scanf("%lld",&num) ;

        ll mx = 0 , mn = 0 ;
        for(int i = 0 ; i < n ; i++){
              if(s[i] == 'p')
                  mx += (1LL << (n - i - 1)) ;
              else
                  mn -= (1LL << (n - i - 1)) ;
        }

        if(num > mx || num < mn){
              puts("Impossible");
              continue ;
        }

        string res(n , '0');
        for(int i = 0 ; i < n ; i++)
              if(s[i] == 'p') res[i] = '1' ;

        ll diff = mx - num ;
        for(int i = 0  ; i < n  ; i++){
              if( (1LL << (n - i - 1)) <= diff ){
                   diff -= (1LL << (n - i - 1)) ;
                   if(s[i] == 'p') res[i] = '0';
                   else res[i] = '1' ;
              }
        }

        printf("%s\n",res.c_str()) ;
    }

    return 0;
}
