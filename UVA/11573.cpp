#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

vector < int > grid[1100];
int n , m ;
const int inf = (1 << 30) ;

int di[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};
int dj[] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int bfs(int si , int sj , int ti , int tj){

    vector < int > dist(n * m + 1 , inf);
    deque < pair < int , int  > > Q ;

    Q.push_back({si , sj});
    dist[si * m + sj] = 0 ;

    while(!Q.empty()){
         auto p = Q.front() ;
         Q.pop_front();

         int i = p.first , j = p.second ;

         if(i == ti && j == tj) return dist[i * m + j];

         int u = i * m + j ;


         for(int k = 0 ; k < 8 ; k++){
                int wi = i + di[k] , wj = j + dj[k] ;
                int v = wi * m + wj ;
                if(wi < 0 || wi >= n || wj < 0 || wj >= m) continue ;
                if(k == grid[i][j]){
                    if(dist[v] > dist[u]){
                         dist[v] = dist[u];
                         Q.push_front({wi , wj});
                    }
                }
                else{
                    if(dist[v] > dist[u] + 1){
                          dist[v] = dist[u] + 1;
                          Q.push_back({wi , wj});
                    }
                }
         }
    }

    return dist[ti * m + tj];
}

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    cin >> n >> m ;

    for(int i = 0 ; i < n ; i++){
        string s; cin >> s ;
        for(auto c : s){
              grid[i].push_back(c - '0');
        }
    }

    int q; cin >> q ;
    while(q--){
         int si , sj , ti ,tj ;
         cin >> si >> sj >> ti >> tj ;
         si-- , sj-- , ti-- , tj-- ;
         cout << bfs(si , sj , ti ,tj) << endl ;
    }



    return 0;
}
