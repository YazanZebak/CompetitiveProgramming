/*
    Idea:
        - This problem can be solved in many different ways
        - 1) Simple DFS: https://codeforces.com/contest/1156/submission/53620605
        - 2) DP on Trees: https://codeforces.com/contest/1156/submission/53636824
        - 3) Centroid Decomposition: My Solution
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 200001 ;
int P[N] , subTree[N] ;
bool blocked[N] ;
vector < pair < int , int > > G[N] ;

void get_size(int u , int p){
     subTree[u] = 1 ;
     P[u] = p ;
     for(auto v : G[u]){
          if(v.first == p || blocked[v.first]) continue ;
          get_size(v.first , u);
          subTree[u] += subTree[v.first];
     }
}

ll zero , one , zero_one , one_zero , res ;


void calc(int u , int p , int state , int last){

    if(state == 1) zero ++ ;
    else if(state == 2) one ++ ;
    else if(last == 1) one_zero ++ ;
    else zero_one ++ ;

    for(auto v : G[u]){
          if(v.first == p || blocked[v.first]) continue ;
          if(state == 3 && v.second != last) continue ;
          calc(v.first , u , state | v.second , v.second);
    }

}

void dfs(int u , int p , int state , int last){

    if(state == 1) res += ( 2 * zero + zero_one + one);
    else if(state == 2) res += (zero + 2 * one + one_zero) ;
    else if(last == 1) res += one ;
    else res += zero ;

    for(auto v : G[u]){
          if(v.first == p || blocked[v.first]) continue ;
          if(state == 3 && v.second != last) continue ;
          dfs(v.first , u , state | v.second , v.second);
    }
}

ll solve(int u){

   zero = one = zero_one = one_zero = 0 ;
   ll ret = 0 ;

   for(auto v : G[u]){
       if(blocked[v.first]) continue ;
       res = 0 ;
       dfs(v.first , u , v.second , v.second);
       ret += res  ;
       calc(v.first , u , v.second , v.second);
   }

   ret += (2 * (zero + one) + zero_one + one_zero) ;

   return ret;
}

ll get_centroid(int src){

    get_size(src , src) ;

    int centroid = src , best = subTree[src];
    queue < int > Q ;
    Q.push(src) ;

    while(!Q.empty()){
         int u = Q.front() ;
         Q.pop();

         int size = subTree[src] - subTree[u] ;
         for(auto e : G[u]){
             int v = e.first ;
             if(v == P[u] || blocked[v]) continue ;
             Q.push(v);
             size = max(size , subTree[v]);
         }

         if(best > size){
               best = size ;
               centroid = u ;
         }
    }

    blocked[centroid] = true ;
    ll ret = solve(centroid) ;
    for(auto v : G[centroid]){
          if(blocked[v.first]) continue ;
          ret += get_centroid(v.first);
    }

    return ret ;
}




int main() {

	ios::sync_with_stdio(0); cin.tie(); cout.tie();

	int n ; cin >> n ;

	for(int i = 0 ; i < n - 1 ; i++){
          int u , v , w ;
          cin >> u >> v >> w;
          G[u].push_back({v , w + 1});
          G[v].push_back({u , w + 1});
	}

	cout << get_centroid(1) << endl ;

	return 0;
}

