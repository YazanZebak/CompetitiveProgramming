// Editorial : https://csacademy.com/contest/ioi-2016-training-round-1/task/hallway/solution/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;


double G[5003][5003];

double dist(pair < int , int > a , pair < int , int > b){
      double x = a.first - b.first ;
      x *= x * 1.0 ;
      double y = a.second - b.second ;
      y *= y * 1.0;
      return sqrt(x + y) ;
}

double dijkstra(int src, int trg , int n){

    vector < double > mini(n , 1e8);
    mini[src] = 0;

    vector < bool > vis(n , 0);

    while(!vis[trg]) {
        double mn = 1e9;
        int idx = -1;

        for(int i = 0; i < n ; i++) {
            if(vis[i]) continue;

            if(mini[i] < mn){
                mn = mini[i];
                idx = i;
            }
        }
        vis[idx] = true;

        for(int i = 0 ; i < n ; i++) {
            auto cost = max(mini[idx] , G[idx][i]);
            if (cost < mini[i])
                mini[i] = cost;
        }

    }

    return mini[trg] / 2.0 ;
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);

    int w , h , n ;
    cin >> w >> h >> n ;

    vector < pair < int , int > > cord;

    for(int i = 0 ; i < n ; i++){
          int x , y ;
          cin >> x >> y ;
          cord.push_back({x , y});
    }

    for(int i = 0 ; i < n ; i++){
         G[i][n] = G[n][i] = dist(cord[i] , make_pair(cord[i].first , h));
         G[i][n + 1] = G[n + 1][i] = dist(cord[i] , make_pair(cord[i].first , 0));

         for(int j = i + 1 ; j < n ; j++){
               double d = dist(cord[i] , cord[j]);
               G[i][j] = G[j][i] = d ;
         }
    }

    G[n][n + 1] = G[n + 1][n] = h ;


    cout << fixed << setprecision(8) << dijkstra(n , n + 1 , n + 2) << endl ;

    return 0;
}
