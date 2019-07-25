// Sol : https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Codeforces/CF101147-GYM-I.txt
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

struct event{
    double x;
    int type, r;
    event(){}
    event(double x, int r, int type) : x(x) , r(r) , type(type) {}
    bool operator < (const event &e){
         if(e.x != x) return x < e.x ;
         return type < e.type;
    }
};



int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    int t ; cin >> t ;

    while(t--){
          ll n , R;
          cin >> n >> R ;

          vector < event > ve;

          for(int i = 0 ; i < n ; i++){
                 ll x, y, r;
                 cin >> x >> y >> r;
                 if(r > R) continue ;
                 ll d = (R - r) * (R - r) - (y * y);
                 if(d < 0) continue ;
                 ve.push_back(event(x - sqrt(d * 1.0) , r , 0));
                 ve.push_back(event(x + sqrt(d * 1.0) , r , 1));
          }

          sort(ve.begin() , ve.end());

          ll res = 0 , sum = 0;

          for(auto i : ve){
               if(i.type == 0) sum += i.r ;
               else sum -= i.r ;
               res = max(res , sum);
          }

          cout << res << endl ;
    }



    return 0;
}
