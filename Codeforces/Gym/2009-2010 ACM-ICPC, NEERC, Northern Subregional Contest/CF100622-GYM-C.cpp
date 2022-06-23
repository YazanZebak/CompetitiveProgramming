/*
	Idea:
		- for each column get it's intersection with the circles
		- we can do that in many ways the easiest is to check if the Cx cord is in the range[x[i] - r[i] , x[i] + r[i]]
		- and we get the intersection points by (y[i] +/- dist ) we get dist by pythagorean theorem  
		- now we have ranges we just need to count the gaps between it, we can do that by sweep line.
*/
#include <bits/stdc++.h>
typedef long long ll ;
using namespace std;

const int N = 102 ;

struct event{
     int idx, t;
     event() {}
     event(int idx , int t) : idx(idx) , t(t) {}
     bool operator < (const event &e){
          if(idx != e.idx) return idx < e.idx;
          return t > e.t;
     }
};

int x[N] , y[N] , r[N];

int main() {

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0) ;

    freopen("circles.in" , "r" , stdin);
    freopen("circles.out" , "w" , stdout);

    int w , h , n ;
    cin >> w >> h >> n ;


    for(int i = 0 ; i < n ; i++)
         cin >> x[i] >> y[i] >> r[i] ;

    int res = 0 ;

    for(int cx = 0 ; cx < w ; cx++){
         vector < event > events ;

         for(int i = 0 ; i < n ; i++){
             if(x[i] - r[i] <= cx && cx <= x[i] + r[i]){
                    int d = sqrt(1.0 * (r[i] * r[i] - (x[i] - cx) * (x[i] - cx)));
                    events.push_back(event(max(y[i] - d, 0) ,  1));
                    events.push_back(event(min(y[i] + d + 1 , h) , -1));
             }
         }

         events.push_back(event(0 , 0));
         events.push_back(event(h , 0));

         sort(events.begin() , events.end());

         int cnt = 0 ;

         for(int i = 0 ; i < events.size() - 1  ; i++){
               if( (cnt += events[i].t) == 0 )
                    res += events[i + 1].idx - events[i].idx;
         }
    }

    cout << res << endl ;


    return 0;
}
