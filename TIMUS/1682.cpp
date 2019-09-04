#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

const int N = 2 * 1e5 + 10 ;
int par[N];

int get(int u){
    if(u == par[u]) return u ;
    return par[u] = get(par[u]);
}

void link(int u , int v){
     u = get(u) , v = get(v);
     par[v] = u ;
}

vector < ll > mod[2][N];

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    ll k ; cin >> k ;

    for(int i = 1 ; i <= 2 * k +  1 ; i++)
           par[i] = i ;

    for(ll i = 1 ;  i <= 2 * k + 1 ; i++){

          ll x = i % k ;
          ll y = (i * i) % k ;

          set < int > se ;

          for(auto j : mod[1][(k - x) % k]){
                  se.insert(j);
          }

          for(auto j : mod[0][(k - y) % k]){
                  se.insert(j);
          }

          for(auto t1 : se)
             for(auto t2 : se)
                   if(t1 != t2 && get(t1) == get(t2))
                             return cout << i << endl , 0 ;

         for(auto j : se)
               link(j , i);

          mod[0][x].push_back(i);
          mod[1][y].push_back(i);
    }

    return 0;
}
