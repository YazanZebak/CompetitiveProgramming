#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , cnt  , root ;
vector < int > ve ;

int dp[100001] , nxt[100001] , last[100001];

int where(int i){
    if(i >= n)
        return cnt ;
    return i / root ;
}

void update(int i){

     if(where(i) != where(i + ve[i])){
         dp[i] = 1;
         nxt[i] = min(n , i + ve[i]);
         last[i] = i ;
     }
     else{
         dp[i] = 1 + dp[i + ve[i]] ;
         last[i] = last[i + ve[i]] ;
         nxt[i] = nxt[i + ve[i]] ;
     }
}

int main()
{
    int q ;
    scanf("%d%d",&n,&q);

    root = sqrt(n) ;

    cnt = (n + root - 1) / root ;

    for(int i = 0 ; i < n ; i++){
         int x ; scanf("%d",&x) ;
         ve.push_back(x) ;
    }

    for(int i = n - 1 ; i >= 0 ; i--)
         update(i) ;

    while(q--){
          int c ; scanf("%d",&c);
          if(!c){

              int idx , val ;
              scanf("%d%d",&idx,&val);

              idx -- ;

              ve[idx] = val ;

              for(int i = idx ; i % root ; i--)
                   update(i) ;

              update(idx / root * root) ;
          }
          else{
              int a ; scanf("%d",&a);
              a-- ;
              int res = 0 , idx = 0 ;
              for(int i = a ; i < n ; i = nxt[i]){
                    res += dp[i] ;
                    idx = last[i] ;
              }
              printf("%d %d\n",idx + 1 ,res) ;
          }
    }

    return 0;
}
