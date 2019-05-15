/*
    Idea:
      - MVC with modification...
      - keep the same algorithm except for leafs , it should be covered from it's parent or it should be a server 
      - for a server node we can do simple pick or leave on it's child
      - if node is not a server we should pick excatly one of it's child as a server and leaves the others... 
      - if node before me is a server , I have to leave all child  
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < vector < int > > tree , G;

void dfs(int u , int p){

    for(auto v : tree[u]){
           if(v == p) continue ;
           dfs(v , u);
           G[u].push_back(v);
    }
}

ll memo[10005][3][3];

ll MVC(int node, bool flag, bool parent) {

    ll &ret = memo[node][flag][parent];

    if(ret != -1)
        return ret ;

    else if(G[node].size() == 0)
        ret = (flag == 0 ? (parent ? 0 : (1LL << 30)) : 1) ;

    else if(flag) {
        ret = 1 ;
        for(auto child : G[node]) {
            ret += min( MVC(child, 1 , flag), MVC(child, 0 , flag) ) ;
        }
    }

    else {
        ret = 0 ;

        if(parent) {
            for(auto child : G[node]) {
                ret += MVC(child, 0 , flag);
            }
        }
        else{
             ret = INT_MAX ;

             ll tot = 0 ;

             for(auto child : G[node]){
                  tot += MVC(child , 0 , flag);
             }

             for(auto child : G[node]){
                  ret = min(ret,  tot - MVC(child , 0 , flag) + MVC(child , 1 , flag));
             }

        }

    }

    return ret ;
}

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int n ;

    while(cin >> n){

          tree.clear() , G.clear() ;
          tree.resize(n + 1) , G.resize(n + 1) ;

          for(int i = 0 ; i < n - 1 ; i++){
              int u , v ;
              cin >> u >> v ;
              tree[u].push_back(v);
              tree[v].push_back(u);
          }

          memset(memo , -1 , sizeof memo);

          dfs(1 , -1) ;
          cout << min(MVC(1 , 0 , 0) , MVC(1 , 1 , 0)) << endl ;

          int x ; cin >> x ;
          if(x == -1) break ;
    }


    return 0;
}
