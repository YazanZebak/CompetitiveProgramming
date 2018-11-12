#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

typedef complex < int > point ;
#define X  real()
#define Y  imag()

struct line{
     point st , en ;
     line(point p1 , point p2) {
          if(p1.Y < p2.Y){
               st = p2 ;
               en = p1 ;
          }
          else{
              st = p1 ;
              en = p2 ;
          }
     }
     bool operator < (const line &l) const{
          return en.Y < l.en.Y ;
     }
};

int main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0) ;

    int t ; cin >> t;

    while(t--){

        int n ; cin >> n ;
        vector < line > ve ;
        for(int i = 0 ; i < n ; i++){
               int x , y ;
               cin >> x >> y ;
               point p1(x , y) ;
               cin >> x >> y ;
               point p2(x , y);
               ve.push_back(line(p1 , p2));
        }

        sort(ve.rbegin() , ve.rend()) ;

        int m ; cin >> m ;
        while(m--){
              int x , y;
              cin >> x >> y ;
              point res(x , y);
              for(int i = 0 ; i < n ; i++){
                   point st = ve[i].st ;
                   point en = ve[i].en ;
                   if( ( (res.X >= st.X && res.X <= en.X) || (res.X >= en.X && res.X <= st.X) ) && res.Y > en.Y ){
                     res = en ;
                   }
              }
              cout << (int)res.X << endl ;
        }

        if(t) cout << "\n" ;
    }

    return 0;
}
