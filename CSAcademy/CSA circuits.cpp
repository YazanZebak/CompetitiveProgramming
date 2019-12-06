#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int n , m ;
ll k ;
vector < int > G[20];
ll memo[18][1 << 18];

ll solve(int last, int mask){

    if(last == 0 && mask == (1 << n) - 1) return 1;
    if(last == 0) return 0 ;
    if(mask == (1 << n) - 1) return 0;

    ll &ret = memo[last][mask];
    if(ret != -1) return ret;

    ret = 0 ;
    for(auto v : G[last]){
          if(mask & (1 << v)) continue ;
          ret += solve(v, mask | (1 << v));
    }

    return ret;
}



int main()
{

    scanf("%d%d%lld",&n,&m,&k);

    for(int i = 0 ; i < m ; i++){
          int u , v ;
          scanf("%d%d",&u,&v);
          u-- , v-- ;
          G[u].push_back(v);
    }

    for(int i = 0 ; i < n ; i++){
          sort(G[i].begin() , G[i].end());
    }

    memset(memo, -1 , sizeof memo);

    vector < int > res ;
    res.push_back(0);

    int mask = 0 ;

    for(int i = 1 ; i < n ; i++){
         for(auto j : G[res.back()]){
              if( j == 0  || (mask & (1 << j)) ) continue ;
              ll tot = solve(j, mask | (1 << j));
              if(tot >= k){
                   res.push_back(j);
                   mask |= (1 << j);
                   break;
              }
              else k -= tot ;
         }
    }

    if(res.size() == n){
          res.push_back(0);
          for(auto i : res) printf("%d ",i + 1);
    }
    else puts("0");



    return 0;
}
