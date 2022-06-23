// editorial : https://github.com/jonathanirvings/icpc-jakarta-2018/blob/master/icpc18-analysis.pdf
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int n , m ; cin >> n >> m;

    vector < int > A , B ;

    int now = 0 , solve = 0 ;

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x;
          A.push_back(x);
    }

    for(int i = 0 ; i < n ; i++){
          if(now + A[i] > m) break ;
          now += A[i];
          solve ++ ;
    }

    if(solve == 0) return cout << -1 << endl , 0;

    for(int i = 0 ; i < n ; i++){
          int x ; cin >> x ;
          B.push_back(x);
    }

    vector < int > maxi(n + 1 , 0);

    for(int i = solve - 1 ; i >= 0 ; i--){
        maxi[i] = max(maxi[i + 1] , B[i]);
    }

    now = 0;
    int cnt_balloon = 0, j = 0;
    int sum = 0;

    vector < int > res ;

    for(int i = 0 ; i < solve ; i++){
          now += B[i] ;

          if(now > m){
               cout << res.size() << endl ;
               for(auto i : res) cout << i << " " ;
               cout << endl ;
               return 0 ;
          }

          while(j < n && sum + A[j] <= now){
                 sum += A[j];
                 cnt_balloon++;
                 j++;
          }

          if(maxi[i] == B[i] && cnt_balloon){
                 res.push_back(now);
                 cnt_balloon--;
                 i-- ;
          }
          else continue ;
    }

    cout << -1 << endl ;


    return 0;
}
