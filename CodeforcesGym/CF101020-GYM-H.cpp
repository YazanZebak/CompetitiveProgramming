#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
#define INF 500000
int G[105][105];
int main() {

    int t = 0 , c = 1  ;
    scanf("%d",&t);
    while(t--) {
        int n , m , f ;
        scanf("%d%d%d",&n,&m,&f);

        for(int i = 1 ; i <= n ; i++)
            for(int j = 1 ; j <= n  ; j ++) {
                if(i == j)
                    G[i][j] = 0 ;
                else
                    G[i][j] = INF ;
            }

        for(int i = 0 ; i < m ; i++) {
            int u , v , w ;
            scanf("%d%d%d",&u,&v,&w);
            G[u][v] = w;
            G[v][u] = w;
        }

        for(int k = 1 ; k <= n ; k++)
            for(int i = 1  ; i <= n ; i++)
                for(int j = 1 ; j <= n ; j++)
                    G[i][j] = min(G[i][j] , G[i][k] + G[k][j]);

        set < int > s;


        for(int i = 0 ; i < f ; i++) {
            int x;
            scanf("%d",&x);
            s.insert(x);
        }
        vector < int > v ;

        set < int > ::iterator it = s.begin();
        for( ; it != s.end() ; it++)
            v.push_back(*it);

        sort(v.begin() , v.end());

        int x = v.size();
        ll ans = INT_MAX;
        do {

            ll cnt = G[1][v[0]] ;

            for(int i = 0  ; i < x - 1  ; i++)
                cnt += G[v[i]][v[i+1]] ;
            cnt += G[v[x-1]][n] ;

            ans = min(ans, cnt);

        } while(next_permutation(v.begin()  , v.end() ));

        printf("Case %d: %I64d",c,ans);
        if(t)
            printf("\n");

        c++;
    }

    return 0;
}
