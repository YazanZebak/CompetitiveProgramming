/*
     Idea:
          - let's calc the contribution for each path to the total answer.
          - for each centroid node, we calc the answer for each path cross from this node.
          - to do this we need to maintain a cnt array to count for the ith bit how many times it appears as zero/one 
          - in the path from the centroid node to it's child. (update)
          - to merge paths, we look at our path and we count for each bit in it how many times it would appear as 1 in other paths 
          - that start from the centroid node and end in one of it's child and add it to the answer. (dfs)
          - let's say we have a path its value 5 : 000..00101 for each bit we look for the opposite bit 111..11010 becuase we xoring
          - and we care only about the active bits, and the contribution of the ith bit is cnt[i][!bit] * 2^i . 
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 10 ;
int A[N];
int n ;
vector < int > G[N];

int sub[N] , par[N];
bool blocked[N];

void get_size(int u , int p){
     sub[u] = 1 ;
     par[u] = p ;
     for(auto v : G[u]){
          if(v == p || blocked[v]) continue ;
          get_size(v , u);
          sub[u] += sub[v];
     }
}

ll cnt[40][2];

ll dfs(int u , int p , int d , int diff){

   ll ret = d ;

   for(int i = 0 ; i < 25 ; i++){
        bool bit = (d ^ diff) & (1 << i);
        ret += (cnt[i][!bit] * (1LL << i));
   }

   for(auto v : G[u]){
        if(v == p || blocked[v]) continue ;
        ret += dfs(v , u , d ^ A[v] , diff);
   }

   return ret;
}


void update(int u , int p , int d){

    for(int i = 0 ; i < 25 ; i++){
          bool bit = d & (1 << i);
          cnt[i][bit]++;
    }

    for(auto v : G[u]){
          if(v == p || blocked[v]) continue;
          update(v , u , d ^ A[v]);
    }

}


ll solve(int u){

    memset(cnt , 0 , sizeof cnt);

    ll ret = A[u];

    for(auto v : G[u]){
          if(blocked[v]) continue ;
          ret += dfs(v , u , A[v] ^ A[u] , A[u]);
          update(v , u , A[v] ^ A[u]);
    }

    return ret;
}


ll get_centroid(int src){

    get_size(src , src);

    queue < int > Q;
    Q.push(src);
    int centroid = src , best = sub[src] ;
    while(!Q.empty()){
           int u = Q.front();
           Q.pop() ;

           int size = sub[src] - sub[u];
           for(auto v : G[u]){
               if(v == par[u] || blocked[v]) continue ;
               Q.push(v);
               size = max(size , sub[v]);
           }

           if(best > size){
               best = size ;
               centroid = u ;
           }
    }

    blocked[centroid] = true;

    ll ret = solve(centroid);

    for(auto v : G[centroid]){
          if(blocked[v]) continue;
          ret += get_centroid(v);
    }


    return ret ;
}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n ;

    for(int i = 1 ; i <= n ; i++){
          cin >> A[i];
    }

    for(int i = 0 ; i < n - 1 ; i++){
          int u , v ;
          cin >> u >> v ;
          G[u].push_back(v);
          G[v].push_back(u);
    }

    cout << get_centroid(1) << endl ;

    return 0;
}
