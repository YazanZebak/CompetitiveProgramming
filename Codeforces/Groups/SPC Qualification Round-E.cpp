#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 10 ;
int tree[4 * N];
vector < int > G[N] , last[N] , ve;
vector < pair < int , int > > Q[N];
int res[N];


void update(int val , int i , int s = 0 , int e = N - 1 , int p = 1){

     if(s > i || e < i) return ;

     if(s == e){
           tree[p] = val ;
           return ;
     }
     update(val , i , s , (s + e)/2 , 2 * p);
     update(val , i , (s + e)/2 + 1 , e , 2 * p + 1);
     tree[p] = min(tree[2 * p] , tree[2 * p + 1]);
}

int query(int val , int s = 0 , int e = N - 1 , int p = 1){
    if(s == e)
         return s ;
    if(tree[2 * p] < val)
          return query(val , s , (s + e) / 2 , 2 * p);
    return query(val , (s + e)/2 + 1 , e , 2 * p + 1);
}

void dfs(int u , int p , int d){

     update(d , ve[u]);
     last[ve[u]].push_back(d);

     for(auto q : Q[u]){
          res[q.second] = query(d - q.first);
     }

     for(auto v : G[u]){
          if(v == p) continue ;
          dfs(v , u , d + 1);
     }

     last[ve[u]].pop_back();

     if(last[ve[u]].empty()) update(-1 , ve[u]);
     else update(last[ve[u]].back() , ve[u]);
}

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int n ; cin >> n ;

    ve.push_back(0);

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x ;
          ve.push_back(x);
    }

    for(int i = 2 ; i <= n ; i++){
          int x ; cin >> x ;
          G[x].push_back(i);
          G[i].push_back(x);
    }

    int q ; cin >> q ;

    for(int i = 0 ; i < q ; i++){
          int u , k ;
          cin >> u >> k ;
          Q[u].push_back({k , i});
    }

    memset(tree , -1 , sizeof tree);

    dfs(1 , -1 , 0);

    for(int i = 0 ; i < q ; i++){
          cout << res[i] << endl ;
    }

    return 0;
}
