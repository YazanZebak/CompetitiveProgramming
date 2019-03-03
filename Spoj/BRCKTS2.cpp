/*
    Idea:
        - first we need to form a tree from the given sequence.
        - for each '(' make a new node and connect the new node with the last unclosed '(' node.
        - for each ')' close the last '(' we have , we can do it easily using stack.
        - now we have our tree the answer for each node is :
        - width = size of the subtree for this node * 2 - 1 , number of open '(' + number of close ')' - 1
        - height = maximum depth from this node to it's child , number of nested brackets '()'
        - for each even level subtract (width * height) else add (width * height)

*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < vector < int > > G;
ll subTree[350001] , maxi[350001];
ll res = 0 ;

void dfs(int u , int p , int l = 1){
    subTree[u] = 1 ;
    maxi[u] = 1 ;
    for(auto v : G[u]){
         if(v == p) continue ;
         dfs(v , u , l + 1) ;
         maxi[u] = max(maxi[u] , maxi[v] + 1);
         subTree[u] += subTree[v];
    }


    res += (l & 1 ? 1 : -1) * (subTree[u] * 2 -  1) * maxi[u];
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
          string s ; cin >> s ;

          G.clear();
          G.resize((int)s.size()) ;

          stack < int > st ;
          int cnt = 0 ;

          memset(subTree , 0 , sizeof subTree) ;

          for(int i = 0 ; i < (int)s.size() ; i++){

                   if(s[i] == ')'){
                        st.pop() ;
                        continue ;
                   }
                   cnt ++ ;
                   if(!st.empty()){
                       G[cnt].push_back(st.top());
                       G[st.top()].push_back(cnt) ;
                   }
                   st.push(cnt) ;
          }
          res = 0 ;

          for(int i = 1 ; i <= cnt ; i++){
                 if(subTree[i]) continue ;
                 dfs(i , -1) ;
          }

          cout << res << endl;
    }



    return 0;
}
