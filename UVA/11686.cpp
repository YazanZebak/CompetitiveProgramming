#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1000003 ;
vector < vector < int > > G ;
vector < int > topsort ;
int indegree[N] , start[N] , finish[N] , timer = 0 ;
bool vis[N];


void dfs(int node , bool &cycle) {

    start[node] = timer ++ ;

    for(auto child : G[node]) {
        if(start[child] == -1)
            dfs(child , cycle);
        else if(finish[child] == -1) {
            cycle = true ;
            break ;
        }
    }

    finish[node] = timer ++ ;
}

void dfs(int node) {

    if(vis[node]) return ;

    vis[node] = 1;

    for(auto child : G[node])
        dfs(child) ;

    topsort.push_back(node) ;
}

void inti(int n) {

    timer = 0 ;
    G.clear() ;
    topsort.clear() ;
    memset(start , -1 , sizeof start) ;
    memset(finish , -1 , sizeof finish) ;
    memset(vis , 0 , sizeof vis) ;
    memset(indegree , 0 , sizeof indegree) ;
    G.resize(n + 1) ;
}

int main() {
    ios::sync_with_stdio(false) ;

    int n , m ;

    while(cin >> n >> m && n && m) {

        inti(n) ;

        for(int i = 0 ; i < m ; i++) {
            int u , v ;
            cin >> u >> v ;
            G[v].push_back(u) ;
            indegree[u]++ ;
        }

        bool cycle = 0 , ok = 0 ;

        for(int i = 1 ; i <= n && !cycle ; i++)
            if(indegree[i] == 0) {
                ok = 1 ;
                dfs(i , cycle) ;
            }

        if(cycle || !ok) {
            cout << "IMPOSSIBLE" << endl ;
            continue ;
        }

        for(int i = 1 ; i <= n ; i++) {
            if(indegree[i] == 0)
                dfs(i) ;
        }

        for(auto i : topsort) cout << i << endl ;
    }



    return 0;
}
