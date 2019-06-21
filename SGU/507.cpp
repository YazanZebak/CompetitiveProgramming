#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 5e4 + 10 ;

int res[N] ;
int sz[N] , val[N];
bool big[N] , isLeaf[N];
vector < int > G[N];


void dfs(int u, int p){
    sz[u] = 1;
    for(auto v : G[u]){
         if(v == p) continue;
         dfs(v , u);
         sz[u] += sz[v];
    }
}

multiset < int > se ;

int add(int u , int p , int sign){

    int ret = 2147483647 ;

    if(sign == -1 && isLeaf[u]) se.erase(se.find(val[u]));
    if(sign == 1 && isLeaf[u]){
          auto it = se.lower_bound(val[u]);
          if(it != se.end()){
                int c1 = *it ;
                ret = min(ret , abs(c1 - val[u]));
                if(it != se.begin()){
                      it -- ;
                      int c2 = *it ;
                      ret = min(ret , abs(c2 - val[u]));
                }
          }
          else if(it != se.begin()){
                it--;
                int c1 = *it ;
                ret = min(ret , abs(c1 - val[u]));
          }
          se.insert(val[u]);
    }

    for(auto v : G[u]){
          if(big[v] || v == p) continue ;
          ret = min(ret , add(v , u , sign));
    }

    return ret ;
}

void dfs(int u , int p , bool keep){

     int mx = -1 , bigChild = -1;
     for(auto v : G[u]){
          if(v == p) continue ;
          if(sz[v] > mx){
              mx = sz[v];
              bigChild = v;
          }
     }

     for(auto v : G[u]){
          if(v == bigChild || v == p) continue ;
          dfs(v , u , 0);
           res[u] = min(res[u] , res[v]);
     }

     if(bigChild != -1)
         dfs(bigChild , u , 1) , big[bigChild] = 1 ,  res[u] = min(res[u] , res[bigChild]);

     res[u] = min(res[u] , add(u , p , 1));


     if(bigChild != -1)
          big[bigChild] = 0;
     if(keep == 0)
          add(u , p , -1);

}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    int n , m ;
    cin >> n >> m ;

    for(int i = 1 ; i <= n ; i++)
        res[i] = 2147483647;

    for(int i = 2 ; i <= n ; i++){
          int x ; cin >> x ;
          G[i].push_back(x);
          G[x].push_back(i);
    }

    for(int i = n - m + 1 ; i <= n ; i++){
          cin >> val[i];
          isLeaf[i] = 1;
    }

    dfs(1 , -1);
    dfs(1 , -1 , 0);


    for(int i = 1 ; i <= n - m ; i++){
          cout << res[i];
          if(i != n - m) cout << " " ;
    }


    return 0 ;
}

