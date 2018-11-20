#include <bits/stdc++.h>
typedef long long ll ;
using namespace std ;

vector < int > root ;
vector < vector < int > > G(100500);
set < pair < int , int > > edges ;
bool vis[100500] ;

void dfs(int node) {

    vis[node] = 1;

    for(auto child : G[node]) {
        if(vis[child]) continue ;
        dfs(child);
        auto t1 = edges.find({node , child});
        auto t2 = edges.find({child , node});
        if(t1 != edges.end()) edges.erase(t1);
        if(t2 != edges.end()) edges.erase(t2);
    }

}

int main() {

    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int n , m ;
    cin >> n >> m ;

    for(int i = 0 ; i < m ; i++) {
        int u , v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        edges.insert({u , v});
    }

    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i]) {
            root.push_back(i) ;
            dfs(i) ;
        }
    }

    int szR = root.size() , szE = edges.size() ;

    if(szE < szR - 1) return cout << -1 << endl , 0 ;

    szR -- ;
    cout << szR << endl ;
    for(int i = 0 ; i < szR ; i++) {
        auto it = *edges.begin() ;
        cout << it.first << " " << it.second << " " << root[i] << " " << root[i + 1] << endl;
        edges.erase(edges.begin());
    }

    return 0 ;
}
