#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

const int N = 50004;

int par[3 * N];
int nxt[3 * N];
int prv[3 * N];

void init(int n){
     for(int i = 0 ; i < 3 * n ; i++){
           par[i] = i;
           nxt[i] = (i + n) % (3 * n);
           prv[i] = (i + 2 * n) % (3 * n);
     }
}

int get(int x){
    if(par[x] == x) return x ;
    return par[x] = get(par[x]);
}

void merge(int x , int y){
    x = get(x) , y = get(y);
    if(x != y) par[y] = x;
}

void mergeAll(int x , int y){
     merge(x , y);
     merge(nxt[x] , nxt[y]);
     merge(prv[x] , prv[y]);
}

bool equal(int x , int y){
     return get(x) == get(y);
}

bool same(int x , int y){
     if(equal(nxt[x] , y) || equal(prv[x] , y))
         return false ;
     mergeAll(x , y);
     return true;
}

bool eat(int x , int y){
     return same(x , prv[y]);
}

int main(){

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
          int n , k ;
          cin >> n >> k ;
          init(n);
          int res = 0 ;
          for(int i = 0 ; i < k ; i++){
                 int type , x , y ;
                 cin >> type >> x >> y ;
                 x-- , y-- ;

                 if(x >= n || y >= n){
                      res ++ ;
                      continue ;
                 }

                 if(type == 1)
                       res += !same(x , y);
                 else
                       res += !eat(x , y);
          }

          cout << res << endl ;
    }


    return 0 ;
}
