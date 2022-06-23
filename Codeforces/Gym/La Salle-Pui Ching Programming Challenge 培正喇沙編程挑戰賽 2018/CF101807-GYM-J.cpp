// Editorial :https://lscct.com/challenge/2018solution.pdf
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 5 * 1e5 + 10;
int n ;
vector < pair < int , int > > G[N];
int st[N] , en[N];
int timer = 0 ;

int tree[4 * N] , lazy[4 * N];
void pushLazy(int s , int e , int p){
     if(lazy[p] & 1){
           tree[p] = !tree[p] ;
           if(s != e){
                lazy[2 * p]++;
                lazy[2 * p + 1]++;
           }
     }
     lazy[p] = 0 ;
}

int query(int id , int s = 0 , int e = n - 1 , int p = 1){
     pushLazy(s , e , p);
    if(s > id || e < id) return 0 ;
    if(s == e && s == id) return tree[p];
    return query(id , s , (s + e)/2 , 2 * p) + query(id , (s + e)/2 + 1 , e , 2 * p + 1);
}

void update(int l , int r , int s = 0 , int e = n - 1 , int p = 1){
    pushLazy(s , e , p);
    if(e < l || s > r) return ;
    if(s >= l && e <= r) {
          lazy[p]++;
          pushLazy(s , e , p);
          return ;
    }
    update(l , r , s , (s + e)/2 , 2 * p);
    update(l , r , (s + e)/2 + 1 , e , 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void dfs(int u , int p ,  int sum){
     st[u] = timer ++ ;
     for(auto e : G[u]){
           int v = e.first , ww = e.second ;
           if(v == p) continue ;
           dfs(v , u , ww);
           if(ww) update(st[v] , en[v]);
     }
     en[u] = timer - 1;
}

bool isAncestor(int u , int v){
     return st[u] <= st[v] && en[u] >= en[v] ;
}

struct edge{
    int u, v, w;
    edge(){}
    edge(int u , int v , int w) : u(u) , v(v) , w(w) {}
};

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    memset(tree , 0 , sizeof tree);
    memset(lazy , 0 , sizeof lazy);

    vector < edge > edges ;

    for(int i = 0 ; i < n - 1 ; i ++){
          int u , v , w ;
          cin >> u >> v >> w ;
          u-- , v-- ;
          w %= 2 ;
          edges.push_back(edge(u , v , w));
          G[u].push_back({v , w});
          G[v].push_back({u , w});
    }

    dfs(0 , -1 , 0);

    int q ; cin >> q ;

    while(q--){
          int t , i , j ;
          cin >> t >> i >> j ;
          if(t == 1){
                i-- , j-- ;

                int t = query(st[i]) ^ query(st[j]);

                if(t) cout << "WE NEED BLACK PANDA" << endl ;
                else cout << "JAKANDA FOREVER" << endl ;
          }
          else{
                auto &it = edges[i - 1];
                if(!isAncestor(it.u , it.v))
                     swap(it.u , it.v);

                int u = it.u , v = it.v ;
                j %= 2 ;
                if(it.w != j) update(st[v]  , en[v]) , it.w = j ;

          }
    }




    return 0;
}
