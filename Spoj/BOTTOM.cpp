#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < vector < int > > G , comps ;
int lowLink[5001] , dfsn[5001] , comp[5001];
bool inStack[5001];
stack < int > st ;
int num = 0 ;

void scc(int u){

    dfsn[u] = lowLink[u] = num++ ;
    inStack[u] = 1 ;
    st.push(u);

    for(auto v : G[u]){
         if(dfsn[v] == -1){
              scc(v);
              lowLink[u] = min(lowLink[u] , lowLink[v]);
         }
         else if(inStack[v])
             lowLink[u] = min(lowLink[u] , lowLink[v]);
    }

    if(lowLink[u] == dfsn[u]){
        comps.push_back(vector < int > ());
        int v = -1 ;
        while(v != u){
             v = st.top() , st.pop() , inStack[v] = 0 ;
             comps.back().push_back(v);
             comp[v] = (int)comps.size() - 1 ;
        }

    }

}


int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n , m ;

    while(cin >> n){

        if(!n) break ;

        G.clear();
        G.resize(n + 1) ;

        comps.clear() ;


        memset(inStack , 0 , sizeof inStack);
        memset(comp , -1 , sizeof comp);
        memset(dfsn , -1 , sizeof dfsn);
        memset(lowLink , -1 , sizeof lowLink);

        cin >> m  ;

        for(int i = 0 ; i < m ; i++){
              int u , v ;
              cin >> u >> v ;
              G[u].push_back(v);
        }

        num = 1;
        for(int i = 1 ; i <= n ; i++){
              if(dfsn[i] == -1){
                   scc(i);
              }
        }

        vector < int > res ;
        vector < bool > valid(comps.size() , 1);

        for(int i = 1 ; i <= n ; i++){
              for(auto v : G[i]){
                    if(comp[v] != comp[i]) valid[comp[i]] = 0 ;
              }
        }

        for(int i = 0 ; i < comps.size() ; i++){
              if(valid[i]) {
                   for(auto v : comps[i]) res.push_back(v);
              }
        }

        sort(res.begin() , res.end());

        for(auto i : res) cout << i << " " ;
        cout << endl ;

    }


    return 0;
}
