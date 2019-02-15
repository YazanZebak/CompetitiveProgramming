#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 10 ;

int P[N] , subTree[N] ;
bool blocked[N] ;
int n , k ;
vector < int > G[N] ;

void get_size(int u , int p){

     P[u] = p ;
     subTree[u] = 1;
     for(auto v : G[u]){
          if(v == p || blocked[v]) continue ;
          get_size(v , u) ;
          subTree[u] += subTree[v] ;
     }
}

string s;

void get_centroid(int src , char c = 'A'){

   get_size(src , src) ;

   int centroid = src , best = subTree[src] ;
   queue < int > Q ;
   Q.push(src) ;

   while(!Q.empty()){
         int u = Q.front() ;
         Q.pop() ;

         int size = subTree[src] - subTree[u] ;
         for(auto v : G[u]){
               if(v == P[u] || blocked[v]) continue ;
               Q.push(v) ;
               size = max(size , subTree[v]);
         }

         if(best > size){
              best = size;
              centroid = u ;
         }
   }

   blocked[centroid] = true ;

   s[centroid] = c ;
   for(auto v : G[centroid]){
        if(blocked[v]) continue ;
        get_centroid(v , c + 1) ;
   }

}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    s.resize(n + 1);

    for(int i = 1 ; i < n ; i++){
          int u , v ;
          cin >> u >> v;
          G[u].push_back(v);
          G[v].push_back(u) ;
    }
    get_centroid(1) ;

    for(int i = 1 ; i <= n ; i++)
         cout << s[i] << " " ;

    return 0;
}
