#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

int main() {
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
          vector < int > cnt1(101 , 0) , cnt2(101 , 0);
          int n ; cin >> n ;
          for(int i = 0 ; i < n ; i++){
             int x ; cin >> x ;
             cnt1[x] ++ ;
          }
          cin >> n ;
          for(int i = 0 ; i < n ; i++){
              int x ; cin >> x;
              cnt2[x] ++ ;
          }
          bool res = 1 ;
          cin >> n ;
          for(int i = 0 ; i < n ; i++){
               int x ; cin >> x ;
               if(cnt1[x] == 0) res = 0 ;
          }
          cin >> n ;
          for(int i = 0 ; i < n ; i++){
               int x ; cin >> x;
               if(cnt2[x] == 0) res = 0 ;
          }

          cout << (res ? "yes" : "no") << endl ;
    }


    return 0;
}
