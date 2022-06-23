/*
	Idea:
		- Problem can be solved by two ways online/offline 
		- online solution by dsu ref: https://ideone.com/NhtCxX
		- offline solution goes as follow : 
		- first let's build the tree from the query of the second type and save for each node the query of the first type '?'
		- we should notice that the input forms a forest not a single tree, to get the root for each tree we simply take the largest unvisited subTree. 
		- now we will answer the queries while traversing the tree.
		- we need two segment tree one for simple rmq contain the power of each node in pos depth.
		- and the other one contain the index for each edge as we want to search for the nearst edge such that it's index greater than the query index
		- because such edge has been formed after the query so we can't consider it's solution.
		- I hope it's clear enough :D.  
*/
#include <bits/stdc++.h>
typedef long long ll ;
typedef long double ld ;
using namespace std ;
 
const int N = 1e5 + 10 ;
const int M = 5e5 + 10 ;
const int inf = 1e9 ;
int n , m ;
int tree[2][N << 2] , power[N] , par[N];
vector < pair < int , int > > G[N];
vector < int > query[N];
 
void insert(int pos , int val , bool idx, int s = 0 , int e = n , int p = 1){
 
     if(s > pos || e < pos) return ;
 
     if(s == e){
           tree[idx][p] = val ;
           return ;
     }
 
     insert(pos , val , idx , s , (s + e)/2 , 2 * p);
     insert(pos , val , idx , (s + e)/2 + 1 , e , 2 * p + 1);
 
     if(idx) tree[idx][p] = max(tree[idx][2 * p] , tree[idx][2 * p + 1]);
     else tree[idx][p] = min(tree[idx][2 * p] , tree[idx][2 * p + 1]);
}
 
int get(int val , int s = 0 , int e = n  , int p = 1){
    if(s == e) return s ;
    int mx = tree[1][2 * p + 1];
    if(mx > val) return get(val , (s + e)/2 + 1 , e , 2 * p + 1);
    return get(val , s , (s + e)/2 , 2 * p);
}
 
int rmq(int l , int r , int s = 0 , int e = n  , int p = 1){
    if(s > r || e < l) return inf ;
    if(s >= l && e <= r) return tree[0][p];
    return min(rmq(l , r,  s , (s + e) /2 , 2 * p) , rmq(l , r,  (s + e)/2 + 1,  e , 2 * p + 1));
}
 
 
 
int res[M];
bool vis[N];
 
void dfs(int u , int p , int d){
 
     insert(d , power[u] , 0);
 
     vis[u] = 1 ;
 
     for(auto i : query[u]){
           res[i] = rmq(get(i) , d) ;
     }
 
     for(auto e : G[u]){
           int v = e.first , id = e.second ;
           if(v == p) continue;
           insert(d + 1 , id , 1);
           dfs(v , u , d + 1);
           insert(d + 1 , -inf , 1);
     }
 
     insert(d , inf , 0);
}
 
int sub[N];
void get_size(int u){
     sub[u] = 1;
     for(auto e : G[u]){
           int v = e.first ;
           if(sub[v]){
                sub[u] += sub[v];
                continue ;
           }
           get_size(v);
           sub[u] += sub[v];
     }
}
 
int main(){
 
 
    scanf("%d%d",&n,&m);
 
    for(int i = 1 ; i <= n ; i++){
           scanf("%d",&power[i]);
    }
 
    memset(tree[0] , 0x444 , sizeof tree[0]);
    memset(tree[1] , -0x444, sizeof tree[1]);
 
    insert(0 , inf , 1);
 
    for(int i = 1 ; i <= m ; i++){
           char c ; cin >> c ;
           if(c == '?'){
                int u ; scanf("%d",&u);
                query[u].push_back(i);
           }
           else{
                int u , v ;
                scanf("%d%d",&u,&v);
                G[u].push_back({v , i});
           }
    }
 
    memset(sub , 0 , sizeof sub);
 
    for(int i = 1 ; i <= n ; i++){
           if(!sub[i])
               get_size(i);
    }
 
    vector < pair < int , int > > ve;
 
    for(int i = 1 ; i <= n ; i++){
           ve.push_back({sub[i] , i});
    }
 
    sort(ve.rbegin() , ve.rend());
 
    memset(res , -1 , sizeof res);
 
    for(auto i : ve){
           if(vis[i.second]) continue ;
           dfs(i.second , -1 , 0);
    }
 
    for(int i = 1 ; i <= m ; i++){
          if(res[i] != -1) printf("%d\n",res[i]);
    }
 
    return 0 ;
}