#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int inf = (1LL << 30);
int n , m ;
int x , y , k ;

ll dist[101][11] , cnt[101];
vector < vector < pair < int , int > > > G(101);

ll Dijkstra(int src , int dest) {

    for(int i = 1 ; i <= n ; i++)
        for(int j = 0 ; j <= k ; j++)
            dist[i][j] = inf , cnt[i] = 0 ;

    priority_queue < pair < ll , ll > , vector < pair < ll , ll > > , greater < pair < ll , ll > > > Q ;

    Q.push({0 , src});

    while(!Q.empty()) {

        auto p = Q.top();
        Q.pop() ;

        ll node = p.second , weight = p.first ;
        if(cnt[node] >= k) continue ;

        dist[node][cnt[node]] = weight ;
        cnt[node] ++ ;

        for(auto i : G[node]) {
            ll child = i.first ;
            ll w = i.second ;
            Q.push({weight + w , child});
        }

    }

    return  (dist[dest][k - 1] == inf ? -1 : dist[dest][k - 1]);
}


int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;


    while(cin >> n >> m) {

        if(n == 0 && m == 0) break ;

        cin >> x >> y >> k ;

        G.clear() ;
        G.resize(n + 1);

        for(int i = 0 ; i < m ; i++) {
            int u , v , c ;
            cin >> u >> v >> c ;
            G[u].push_back({v , c});
        }

        cout << Dijkstra(x , y) << endl ;

    }


    return 0;
}
