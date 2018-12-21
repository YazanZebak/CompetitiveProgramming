#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct edge{
    int u , v;
    int a, b;
    edge(int u , int v , int a, int b) : u(u) , v(v) , a(a) , b(b) {}
};
vector < vector < edge > > tree(100);
map < string , int > node ;
map < int , string > name ;

int res1 , res2 ;
void dfs(int u , int v , int parent = -1 , int nem = 1, int dem = 1){

     if(u == v){
          int g = __gcd(nem , dem);
          res1 = dem / g ;
          res2 = nem / g ;
     }

     for(auto e : tree[u]){
          if(e.v == parent) continue ;

          nem *= e.b ;
          dem *= e.a ;
          int g = __gcd(nem , dem) ;
          nem /= g;
          dem /= g;
          dfs(e.v , v , u , nem , dem);
          nem *= g , dem *= g ;
          nem /= e.b ;
          dem /= e.a ;
     }
}

int main() {

    ios::sync_with_stdio(false);
    int cnt = 1;

    char c , eq;

    while(cin >> c && c != '.'){

          if(c == '!'){
              int a ; cin >> a;
              string u ; cin >> u;
              if(node[u] == 0) node[u] = cnt , name[cnt] = u , cnt ++ ;
              cin >> eq ;
              int b ; cin >> b;
              string v ; cin >> v ;
              if(node[v] == 0) node[v] = cnt , name[cnt] = v , cnt ++ ;
              tree[node[u]].push_back(edge(node[u] , node[v] , a , b));
              tree[node[v]].push_back(edge(node[v] , node[u] , b , a));
          }
          else{
               res1 = res2 = 0 ;
               string u ; cin >> u ;
               cin >> eq ;
               string v ; cin >> v ;
               dfs(node[u] , node[v]);
               if(res1 == 0 && res2 == 0)
                    cout << "? " << u << " = ? " << v << endl ;
               else
                    cout << res1 << " " << u << " = " << res2 << " " << v << endl ;
          }
    }


    return 0;
}
