/*
	Idea : https://discuss.codechef.com/t/dincpath-editorial/24492
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 10 ;
const ll inf = 1e16;

vector < pair < int, ll > > G[N] ;
vector < pair < ll, int > > sol[N] ;
vector < int >  maxi[N] ;
vector < int > topsort ;
bool vis[N] ;

void dfs(int u) {

    vis[u] = 1 ;
    for(auto e : G[u]) {
        if(!vis[e.first])
            dfs(e.first) ;
    }

    topsort.push_back(u);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int n, m ;
    cin >> n >> m ;

    for(int i = 0 ; i < m ; i++) {
        int u, v, w ;
        cin >> u >> v >> w ;
        G[u].push_back({v, w});
    }


    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i])
            dfs(i) ;
    }

    int res = 0;

    for(auto u : topsort) {

        sol[u].push_back({inf, 1});

        for(auto e : G[u]) {
            ll w = e.second, v = e.first ;
            int id = upper_bound(sol[v].begin(), sol[v].end(), make_pair(w , 0)) - sol[v].begin() ;
            if(id == sol[v].size())
                continue ;
            sol[u].push_back({w, 1 + maxi[v][id]});
        }
        sort(sol[u].begin(), sol[u].end());

        int mx = 0 ;
        maxi[u].resize(sol[u].size());

        for(int i = sol[u].size() - 1 ; i >= 0 ; i--) {
            mx = max(mx, sol[u][i].second);
            maxi[u][i] = mx ;
        }

        res = max(res, mx);
    }

    cout << res << endl ;



    return 0;
}
