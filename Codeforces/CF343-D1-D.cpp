/*
	Idea:
		- the problem has 3 type of queries.
		- let's processes the first type while going down with simple dfs.
		- let's processes the second type with the same dfs but using dsu on trees.  
		- every time we processes a query we add it's index to a set.
		- when we want to answer a query we just look on the prev of our index.  
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 500002 ;


int sz[N];
vector < int > G[N];
vector < int > Q[N][4];
int res[N];
bool big[N];

void dfs(int u, int p) {
    sz[u] = 1 ;
    for(auto v : G[u]) {
        if(v == p)
            continue ;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

set < int > se ;

void add(int u, int p, int val) {


    if(val == 1)
        for(auto c : Q[u][2])
            se.insert(c);
    else
        for(auto c : Q[u][2])
            se.erase(c);

    for(auto v : G[u]) {
        if(big[v] || v == p)
            continue ;
        add(v, u, val);
    }
}

vector < int > query ;

void dfs(int u, int p, bool keep) {

    int mx = -1, bigChild = -1 ;

    for(auto c : Q[u][1])
        se.insert(c);

    for(auto v : G[u]) {
        if(v == p)
            continue ;
        if(mx < sz[v]) {
            mx = sz[v];
            bigChild = v ;
        }
    }

    for(auto v : G[u]) {
        if(v == p || v == bigChild)
            continue ;
        dfs(v, u, 0);
    }

    if(bigChild != -1)
        dfs(bigChild, u, 1), big[bigChild] = 1 ;

    add(u, p, 1);

    for(auto c : Q[u][3]) {
        auto it = se.lower_bound(c);
        if(it == se.begin()){
            res[c] = 0 ;
            continue ;
        }
        it-- ;
        int id = *it ;
        if(query[id] == 2)
            res[c] = 0 ;
        else
            res[c] = 1 ;
    }

    if(bigChild != -1)
        big[bigChild] = 0 ;
    if(keep == 0)
        add(u, p, -1);

    for(auto c : Q[u][1])
        se.erase(c);

}

int main() {



    int n ; scanf("%d",&n);

    for(int i = 0 ; i < n - 1 ; i++) {
        int u, v ;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int q ; scanf("%d",&q);

    query.push_back(0);


    for(int i = 1 ; i <= q ; i++) {
        int c, v ;
        scanf("%d%d",&c,&v);
        query.push_back(c);
        Q[v][c].push_back(i);
        res[i] = -1 ;
    }

    dfs(1, -1);
    dfs(1, -1, 0);

    for(int i = 1 ; i <= q ; i++) {
        if(res[i] == -1)
            continue ;
        printf("%d\n",res[i]);
    }

    return 0 ;
}
