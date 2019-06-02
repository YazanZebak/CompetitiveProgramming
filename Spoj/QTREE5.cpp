#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 1e5 + 10;
const int Log = 20 ;
const int inf = (1 << 25);

vector < int > G[N] ;
vector < int > tree[N] ;
int P[N][Log], L[N];

int n, q ;

void dfs(int u, int p, int d) {

    P[u][0] = p ;
    L[u] = d ;

    for(auto v : G[u]) {
        if(v == p)
            continue ;
        dfs(v, u, d + 1) ;
    }
}

void dp() {

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; (1 << j) <= n ; j++)
            P[i][j] = -1 ;

    for(int j = 1 ; (1 << j) <= n ; j++)
        for(int i = 1 ; i <= n ; i++)
            if(P[i][j - 1] != -1)
                P[i][j] = P[P[i][j - 1]][j - 1] ;
}


int lca(int u, int v) {

    if(L[u] < L[v])
        swap(u, v);

    int i, log ;
    for(log = 1 ; (1 << log) <= L[u] ; log++);

    log-- ;

    for(i = log ; i >= 0 ; i--) {
        if(L[u] - (1 << i) >= L[v])
            u = P[u][i];
    }

    if(u == v)
        return u ;


    for(i = log ; i >= 0 ; i--)
        if(P[u][i] != -1 && P[u][i] != P[v][i])
            u = P[u][i], v = P[v][i] ;

    return P[u][0] ;
}

int dist(int u, int v) {
    return L[u] + L[v] - 2 * L[lca(u, v)];
}


int par[N], sub[N];
bool blocked[N] ;


void get_size(int u, int p, vector < int > g[]) {

    par[u] = p;
    sub[u] = 1;

    for(auto v : g[u]) {
        if(v == p || blocked[v])
            continue ;
        get_size(v, u, g);
        sub[u] += sub[v];
    }

}
int root ;

int get_centroid(int src) {

    get_size(src, src, G);

    int centroid = src, best = sub[src];
    queue < int > Q;
    Q.push(src);

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop() ;

        int size = sub[src] - sub[u] ;
        for(auto v : G[u]) {
            if(v == par[u] || blocked[v])
                continue ;
            Q.emplace(v);
            size = max(size, sub[v]);
        }

        if(best > size) {
            centroid = u ;
            best = size;
        }
    }

    blocked[centroid] = true;
    for(auto v : G[centroid]) {
        if(blocked[v])
            continue ;
        int child = get_centroid(v);
        tree[centroid].push_back(child);
        tree[child].push_back(centroid);
    }

    return centroid;
}

multiset < int > ans[N];
bool white[N];

void update(int u) {

    if(!white[u]) {
        int v = u ;
        while(true) {
            ans[v].insert(dist(u, v));
            if(v == par[v])
                break;
            v = par[v];
        }
    }

    else {
        int v = u ;
        while(true) {
            ans[v].erase(ans[v].find(dist(u, v)));
            if(v == par[v])
                break;
            v = par[v];
        }
    }

    white[u] = !white[u];
}

int query(int u) {
    int v = u ;
    int ret = inf ;
    while(true) {
        ret = min(ret, *(ans[v].begin()) + dist(u, v));
        if(v == par[v])
            break ;
        v = par[v];
    }

    return (ret == inf ? -1 : ret);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    memset(white, 0, sizeof white);

    cin >> n;

    for(int i = 0 ; i < n - 1 ; i++) {
        int u, v ;
        cin >> u >> v ;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for(int i = 1 ; i <= n ; i++)
        ans[i].insert(inf);

    dfs(1, -1, 0);
    dp();

    root = get_centroid(1);

    memset(blocked, 0, sizeof blocked) ;

    get_size(root, root, tree);

    cin >> q ;

    while(q--) {
        int t, u ;
        cin >> t >> u ;

        if(t == 0)
            update(u);
        else
            cout << query(u) << endl ;
    }

    return 0;
}
