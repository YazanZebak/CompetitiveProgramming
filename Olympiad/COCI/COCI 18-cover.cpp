#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;
 
vector < pair < ll , ll > > vec;
ll memo[5005];
 
const ll inf = 1e18 ;
 
ll solve(int i){
 
   if(i == vec.size()) return 0 ;
 
   ll &ret = memo[i];
   if(ret != -1) return ret ;
 
 
   ll x = vec[i].first ;
 
   ret = inf ;
 
   for(int j = i ; j < (int)vec.size() ; j++){
        ret = min(ret, 4 * x * vec[j].second + solve(j + 1));
   }
 
   return ret ;
}
 
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
 
    int n ;
    cin >> n ;
 
    vector < pair < ll, ll > > ve;
 
    for(int i = 0 ; i < n ; i++) {
        ll x,y  ;
        cin >> x >> y ;
        x = abs(x);
        y = abs(y);
        ve.push_back({x, y});
    }
 
    sort(ve.rbegin(), ve.rend());
 
    vector < bool > vis(n , 0);
 
    for(int i = 0 ; i < n ; i++){
          for(int j = i + 1 ; j < n ; j++){
              if(vis[j]) continue;
              if(ve[i].second < ve[j].second) break ;
              else vis[j] = 1;
          }
    }
 
    for(int i = 0 ; i < n ; i++){
          if(!vis[i]) vec.push_back(ve[i]);
    }
 
    memset(memo , -1 , sizeof memo);
 
    cout << solve(0) << endl;
 
 
    return 0;
}