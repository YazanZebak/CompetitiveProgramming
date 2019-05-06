/*
    Idea:
        - we want to calculate the sum of all paths.
        - we can use "contribution" technique : for each element calc how it's contribute to the total sum.
        - in our problem for each edge how many paths cross from it.
        - this easily can be done by (subTree[v] * (n - subTree[v]))
        - the probability is same for all paths = C(n , 2) + n , (not necessarily distinct)
        - so the final answer is  sum_of_paths / total_number_paths
*/

#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 2e5 + 10 ;
const ll mod = 1e9 + 7 ;

ll sub[N] , n ;
vector < vector < int > > G(N);

inline ll inv(ll a, ll mod){
    return a > 1 ? mod - inv(mod % a, a) * mod / a : 1;
}

void dfs(int u , int p){
     sub[u] = 1;
     for(auto v : G[u]){
          if(v == p) continue ;
          dfs(v , u) ;
          sub[u] += sub[v];
     }
}

ll res = 0 ;
void calc(int u , int p){

    for(auto v : G[u]){
          if(v == p) continue ;
          calc(v , u);
          ll cnt = ( (sub[v] * (n - sub[v])) % mod ) ;
          res += cnt ;
          res %= mod ;
    }
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    ll tot = n * (n - 1) / 2 + n ;
    tot %= mod ;

    for(int i = 0 ; i < n - 1;  i++){
          int u , v ;
          cin >> u >> v ;
          G[u].push_back(v);
          G[v].push_back(u);
    }

    dfs(1 , -1);
    calc(1 , -1);

    res *= inv(tot , mod) ;
    res %= mod ;

    cout << res << endl ;

    return 0;
}
